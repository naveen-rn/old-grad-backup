class GraphGenerator
  def initialize
    @node_group = Hash.new
    @weighted_graph = Hash.new
    @edges_pair = Hash.new
    @connecting_pair = Hash.new
    @edge_pair_id = 0
    @edges = 0
  end

  def validate_node_size(node_size)
	  if node_size%4 == 0
		  true
    else
      false
	  end
  end

  def generate_number_of_unit_group(node_size)
    node_size/4
  end

  def form_unit_group(node_size)
    (1..generate_number_of_unit_group(node_size)).inject(1) do |result, index|
      @node_group[index] ||= [
        ((index - 1)*4)+1, 
        ((index - 1)*4)+2, 
        ((index - 1)*4)+3, 
        ((index - 1)*4)+4 
      ]
    end
    @node_group
  end

  def form_edges(node_group_local)
    (1..node_group_local.size).inject(1) do |result, index|
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][0], node_group_local[index][1]]
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][0], node_group_local[index][2]]
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][0], node_group_local[index][3]]
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][1], node_group_local[index][2]]
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][1], node_group_local[index][3]]
      @edge_pair_id = @edge_pair_id + 1
      @edges_pair[@edge_pair_id] = [node_group_local[index][2], node_group_local[index][3]]
    end
  end

  def add_weight(start_node, end_node)
    @edges = @edges + 1
    @weighted_graph[@edges] = [start_node, end_node, (1+Random.rand(20))]
  end

  def form_connecting_edges
    (1..(@node_group.size-1)).inject(1) do |result, index| 
      @connecting_pair[index] = [
        @node_group[index][2], 
        @node_group[index][3], 
        @node_group[index+1][0], 
        @node_group[index+1][1]
      ]
    end
  end

  def print_edges
    file = File.new("graph.txt", "w") 
    @weighted_graph.each do |k, v|
      file.print v[0],",",v[1],",",v[2]
      file.puts
    end
    file.close
  end

  def creating_graph(node_size)
    if (validate_node_size(node_size))
      form_unit_group(node_size)
      form_edges(@node_group)
      form_connecting_edges
      form_edges(@connecting_pair)
      edges_pair_list = @edges_pair.collect{ |k, v| v}
      edges_pair_list = edges_pair_list.uniq
      (1..edges_pair_list.size-1).inject(1) do |result, index|
        add_weight(edges_pair_list[index][0], edges_pair_list[index][1])
      end
    end
    print_edges
  end
end

GraphGenerator.new.creating_graph(1024*4)