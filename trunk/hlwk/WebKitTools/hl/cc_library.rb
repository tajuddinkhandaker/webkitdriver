# Global hash contains ldflags for required libraries. Library name is a key,
# value is a list of flags for linker
LDFLAGS={}

# Global hash contains cxxflags for required libraries. Library name is a key,
# value is a list of flags for g++
CXXFLAGS={}

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

  unless opts[:defines].nil?
    cxxflags += opts[:defines].map { |x| "-D" + x }
  end

  unless opts[:includes].nil?
    cxxflags += opts[:includes].map { |x| "-I" + x }
  end

  if opts[:install].nil?
    builddir = "./build"
  else
    builddir = opts[:install]
  end
  
  cxxflags = cxxflags.join(" ");
  ldflags = ldflags.join(" ");

  directory(builddir)

  RakeFileUtils.verbose(false);

  count = sources.length;
  deps = []
  sources.each_index do |idx|
        x = sources[idx]
        obj = File::join builddir, File::basename(x, ".cpp") + ".o"
        file obj  => [ x ] do
          puts "[#{idx+1} / #{count}] #{x}"
          sh "g++ -c -o #{obj} -fPIC #{cxxflags} #{x}", :verbose => false
        end
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

