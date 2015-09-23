class Communication
  def initialize
    @input = Hash.new
    @numberofMessages = 0
    @total_time = 0
    @graph_path = Hash.new {|hsh,key| hsh[key] = [] }
    @intermediate = Hash.new {|hsh,key| hsh[key] = [] }
    @temp_time = 0
  end

  def message_count
    @numberofMessages
  end

  def total_time_taken
    @total_time
  end

  def return_intermediate_buffer_for_testing
    @intermediate
  end

  def clear_intermediate_buffer
    @intermediate = Hash.new {|hsh,key| hsh[key] = [] }
  end

  def graph_path_return
    @graph_path
  end

  def graph_covered
    temp_buffer = []
    @graph_path.each_with_index do |(key, value), index|
      temp_buffer.push(key)
    end
    temp_buffer
  end


  def setting_up_values(source)
    @input = source
  end

  def identify_neighbours(node_id)
    ids = Hash.new {|hsh,key| hsh[key] = [] }
    (0..@input[node_id].length-1).inject(0) do |result, index|
      ids[@input[node_id][index][0]] = @input[node_id][index][1]
    end
    ids
  end

  def send_message_to_neighbours(source, dest, weight)
    @numberofMessages += 1
    if @intermediate.has_key?(dest)
      if !(@intermediate[dest][1] < weight)
        @intermediate[dest] = [source, weight]
      end
    else
      @intermediate[dest] = [source, weight]
    end
  end

  def send_confirm_to_parents(source)
    @numberofMessages += 1
    if !@graph_path.has_key?(source)
      @graph_path[source] = @intermediate[source][0]
    end
  end

  def converge_cast(source)
    def converge_cast_recur(source, dest)
      if dest != 1
        @numberofMessages += 1
        converge_cast_recur(dest, @graph_path[dest])
      end
    end
    converge_cast_recur(source, @graph_path[source])
  end

  def form_tree(dest)
    def form_tree_recur(dest, source)
      if source != 1
        @numberofMessages += 1
        form_tree_recur(source, @graph_path[source])
      else
        @numberofMessages += 1
      end
    end
    form_tree_recur(dest, @graph_path[dest])
  end

  def sync_all
    @total_time += 1
  end

  def find_next_neighbour(source_id_list)
    next_neighbour = []
    for index in 0..source_id_list.length-1
      neighbours = identify_neighbours(source_id_list[index])
      neighbours.each_with_index do |(key, value), index|
        next_neighbour.push(key)
      end
    end
    next_neighbour.uniq
  end

  def individual_neighbour(source)
    next_neighbour = []
    neighbours = identify_neighbours(source)
    neighbours.each_with_index do |(key, value), index|
      next_neighbour.push(key)
    end
    next_neighbour
  end
end