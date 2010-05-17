# Global hash contains ldflags for required libraries. Library name is a key,
# value is a list of flags for linker
LDFLAGS={}

# Global hash contains cxxflags for required libraries. Library name is a key,
# value is a list of flags for g++
CXXFLAGS={}

Rake.application.add_loader('dep', Rake::MakefileLoader.new)

def which(name)
   ENV['PATH'].split(":").map {|x| x + '/' + name }.find { |x| File.executable? x }
end

def extra_libraries(*args)
  args.each do |name|
    task name do
      library_config name, "#{name}-config"
    end
  end
end

def extra_libraries_pkgconfig(*args)
  args.each do |name|
    task name do
      library_config name, "pkg-config #{name}"
    end
  end
end

def pkg_config name
  library_config name, "pkg-config #{name}"
end

def library_config(name, cfgtool, cflags='--cflags', libs='--libs')
  if CXXFLAGS[name].nil?
      CXXFLAGS[name] = `#{cfgtool} #{cflags}`.split
      if $? != 0
        raise "Library #{name} is not installed"
      end
  end

  if LDFLAGS[name].nil?
      LDFLAGS[name] = `#{cfgtool} #{libs}`.split
      if $? != 0
        raise "Library #{name} is not installed"
      end
  end
end

# Hash with keys = filename, value = file depends on cc_library::opts[:defines].
# We use it to reduce file IO operations for .dep generation.
DEF_DEP = {}

# Check, are our defines changed? Compare defines form Rakefile & command line
# with stored in .defs file. Rewrite .defs file it they are different.
#
def def_chk(def_arr, def_file_name)
  d_f = File.new(def_file_name, File::RDWR | File::CREAT)
  def_file = d_f.readlines.collect {|x| x.chomp}
  unless def_arr.sort == def_file.sort
    d_f.rewind
    def_arr.each {|x| d_f.puts x}
    d_f.truncate d_f.pos
  end
  d_f.close
  File::delete(def_file_name) if File::stat(def_file_name).zero?
  DEF_DEP.clear
end

# Append .defs file name with our defines to dependencies list.
#
def add_def_dep(dep, def_fname)
  File::open(dep, File::RDWR) do |f|
    f.seek(-1, IO::SEEK_END)
    f.puts " \\", " #{def_fname}"
  end
end

# Make .dep files with make style dependencies.
# Go through list of source dependent files and find #if/#ifdef directives with our
# defines. If they are found add dependecy from .defs file with list of out defines.
#
def mk_dep(dep, src, obj, cxxflags, def_fname, c_defs)
  sh "g++ -MM #{cxxflags} -MT #{obj} -MT #{dep} #{src} > #{dep}", :verbose => false
  unless def_fname.nil?
    # Make dependencies list.
    esc_space = "__&NBSP;__"
    buff = open(dep).read
    buff.gsub!(/\\ /, esc_space)        # Escape spaces in file name.
    buff.gsub!(/#[^\n]*\n/m, "")
    buff.gsub!(/\\\n/, ' ')
    buff.sub!(/\n.*/m, "")
    buff.sub!(/.*:/, "")
    tmp_list = buff.split.collect {|f| f.gsub(/#{esc_space}/, ' ')}

    # Make new list without names from DEF_DEP.
    f_list = []
    tmp_list.each do |x|
      unless DEF_DEP.has_key? x
        f_list << x
        next
      end

      # If file is in DEF_DEP with true, obj depends on def_fname, return.
      if DEF_DEP[x]
        add_def_dep(dep, def_fname)
        return
      end
    end

    # Grep each file from f_list for c_defs. Save boolean info into DEF_DEP.
    # If true, obj depends on def_fname, return.
    f_list.each do |f|
      unless File::open(f).grep(/^\s*#\s*if.*(#{c_defs})/).empty?
        DEF_DEP[f] = true
        add_def_dep(dep, def_fname)
        return
      end
      DEF_DEP[f] = false
    end
  end
end


def cc_library(*args)
  opts = args.pop
  if opts[:name].nil?
    raise "Library name is not specified"
  end
  sources = opts[:srcs].map { |x| Dir::glob(x) }.flatten
  unless opts[:exclude].nil?
    opts[:exclude].each do |pattern|
          sources.reject! do |filename|
            File::fnmatch?(pattern, filename)
          end
    end
  end

  cxxflags = opts[:cxxflags].nil? ? [] : opts[:cxxflags]
  ldflags = opts[:ldflags].nil? ? [] : opts[:ldflags]

  unless opts[:libs].nil?
    opts[:libs].each do |name|
      t = Rake.application.lookup(name)
      unless t.nil?
        t.invoke
        unless CXXFLAGS[name].nil?
          cxxflags |= CXXFLAGS[name]
        end
        unless LDFLAGS[name].nil?
          ldflags |= LDFLAGS[name]
        end
      else
        ldflags |= ["-l#{name}"]
      end
    end
  end

  if opts[:install].nil?
    builddir = "./build"
  else
    builddir = opts[:install]
  end

  use_deps = ENV["WEBKIT_NOT_USE_DEPS"].nil?

  if use_deps
    dep_dir = File::join(builddir, "deps")
    directory(dep_dir)
    Rake::Task[dep_dir].invoke

    # Name of file with defines
    def_fname = File::join(dep_dir, File::basename(opts[:name]) + ".defs")
    c_defs = nil
  end

  directory(builddir)
  Rake::Task[builddir].invoke

  unless opts[:defines].nil?
    cxxflags += opts[:defines].map { |x| "-D" + x }
    if use_deps
      def_chk(opts[:defines], def_fname)
      def_fname = nil if File::stat(def_fname).zero?

      # Make current define names without predefined prefixes.
      rm_pref = "WTF_PLATFORM_|WTF_COMPILER_|WTF_CPU_"
      c_defs = opts[:defines].collect {|x| x.split("=")[0].sub(/#{rm_pref}/, "")}.join("|")
      c_defs.gsub!(/HAVE_/, "HAVE\\(")
      c_defs.gsub!(/WTF_OS_/, "OS\\(")
      c_defs.gsub!(/WTF_USE_/, "USE\\(")
      c_defs.gsub!(/ENABLE_/, "ENABLE\\(")
    end
  end

  unless opts[:includes].nil?
    cxxflags += opts[:includes].map { |x| "-I" + x }
  end

  cxxflags = cxxflags.join(" ");
  ldflags = ldflags.join(" ");

  RakeFileUtils.verbose(false);

  count = sources.length;
  deps = []
  sources.each_index do |idx|
        x = sources[idx]
        obj = File::join builddir, File::basename(x, ".cpp") + ".o"
        if use_deps
          dep = File::join dep_dir, File::basename(x, ".cpp") + ".dep"
          # Create missing .dep files.
          unless FileTest::exist? dep
            puts "[#{idx+1} / #{count}] #{dep}"
            mk_dep(dep, x, obj, cxxflags, def_fname, c_defs)
          end
        end
        # File-rule to make .o and .dep.
        file obj  => [ x ] do
          puts "[#{idx+1} / #{count}] #{x}"
          # If .o is absent we go the first time and .dep is already made above, so skip its making.
          mk_dep(dep, x, obj, cxxflags, def_fname, c_defs) if use_deps && FileTest::exist?(obj)
          sh "g++ -c -o #{obj} -fPIC #{cxxflags} #{x}", :verbose => false
        end
        import dep if use_deps
        deps << obj
  end

  unless opts[:local_static].nil?
    static_libs = opts[:local_static].map { |x| builddir + '/' + x}.join(' ')
  else
    static_libs = ""
  end

  task opts[:name] => [builddir + '/' + opts[:name]]
  extradeps = opts[:deps].nil? ? [] : opts[:deps]
  file builddir + '/' + opts[:name] => [builddir] + extradeps + deps do |t|
    if t.name =~ /\.a$/
      puts "Create static library #{t.name}"
      sh "ar rcs #{t.name} " + deps.join(" ")
    elsif t.name =~ /\.so$/
      puts "Create shared library #{t.name}"
      sh "g++ --shared -fPIC -DPIC -o #{t.name} " + deps.join(" ") + " #{static_libs} #{ldflags}"
    else
      puts "Create executable #{t.name}"
      sh "g++ -o #{t.name} " + deps.join(" ") + " #{static_libs} #{ldflags}"
    end
  end
end
