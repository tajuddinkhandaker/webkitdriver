require 'rake'

task :hlwk do
    Dir.chdir('./hlwk') do
        sh 'rake'
    end
end

task :webdriver => [ :hlwk ] do
    Dir.chdir('./driver') do
        sh 'rake'
    end
end

task :default => [:webdriver]
