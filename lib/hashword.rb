require 'hashword_core.so'

class Array
  def hashword(initval=0)
    ::Object.hashword(self, size, initval)
  end
end
