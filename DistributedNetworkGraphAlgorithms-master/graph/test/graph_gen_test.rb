require 'test/unit'
require './src/graph_gen'

class TestGraphGen < Test::Unit::TestCase
	def test_canary
		assert true
	end

  def test_validate_node_size_for_multiple_of_4
    assert GraphGenerator.new.validate_node_size(4)
  end

  def test_generate_number_of_unit_group_for_4_nodes
    assert_equal 1, GraphGenerator.new.generate_number_of_unit_group(4)
  end

  def test_generate_number_of_unit_group_for_16_nodes
    assert_equal 4, GraphGenerator.new.generate_number_of_unit_group(16)
  end

  def test_generate_number_of_unit_group_for_40_nodes
    assert_equal 10, GraphGenerator.new.generate_number_of_unit_group(40)
  end

  def test_form_unit_group
    assert_equal Hash[1=>[1, 2, 3, 4], 2=>[5, 6, 7, 8], 3=>[9, 10, 11, 12]], 
      GraphGenerator.new.form_unit_group(12)
  end

  def test_main
    GraphGenerator.new.creating_graph(12)
  end
end