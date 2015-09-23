require 'test/unit'
require './src/file_read'

class TestFileRead < Test::Unit::TestCase
	def test_canary
		assert true
	end

  def test_file_path_exists
    assert FileRead.new.check_file_path("test/")
  end

  def test_file_available
    assert FileRead.new.check_file_avail("test/testGraph.txt")
  end

  def test_read_file
    assert_equal [[1,3,9],[1,4,10],[2,3,9]], FileRead.new.read_file("test/testGraph.txt")
  end

  def test_validate_input
    assert_equal Hash[1=>[[3, 9], [4, 10]], 2=>[[3, 9]]], FileRead.new.format_input(FileRead.new.readFile("test/testGraph.txt"))
  end
end