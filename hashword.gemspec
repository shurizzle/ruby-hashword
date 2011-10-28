require 'rubygems'

Gem::Specification.new do |s|
    s.name          = 'hashword'
    s.version       = '0.0.1'
    s.author        = 'shura'
    s.email         = 'shura1991@gmail.com'
    s.homepage      = 'http://github.com/shurizzle/ruby-hashword'
    s.platform      = Gem::Platform::RUBY
    s.summary       = 'Hashword algorithm implementation'
    s.description   = 'Add a method to Array:Class to get hashword\'s hash'
    s.files         = Dir['ext/*'] + Dir['lib/*']
    s.extensions    = 'ext/extconf.rb'
    s.has_rdoc      = true
end
