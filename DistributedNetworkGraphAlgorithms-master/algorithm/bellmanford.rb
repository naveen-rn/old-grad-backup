require '../engine/src/comms'
require '../engine/src/file_read'

class BellmanFord

  def initialize
  	@inputPath = "../build"
	  @inputFile = "../build/graph.txt"	
  	@source = Hash.new 
  	@comms = Communication.new
    @distance = Hash.new {|hsh,key| hsh[key] = []}
    @parent = Hash.new {|hsh,key| hsh[key] = []}
    @termination_count = 0
      @temp_count = []
  end

  def get_input(inputFile)
  	if FileRead.new.check_file_path(@inputPath)
  	  if FileRead.new.check_file_avail(inputFile)
  	  	@source = FileRead.new.format_input(FileRead.new.read_file(inputFile))
  	  end
  	end
  	@source
  end   

  def algorithm(total_nodes)
    def algorithm_init(source_id, total_nodes)
      for index in 1..total_nodes
        if index == source_id
          @distance[index] = 0
          @parent[index] = source_id
        else 
          @distance[index] = @source.length * 1000
          @parent[index] = nil
        end
      end
    end

    def send_message(source, dest, weight)
      @comms.send_message_to_neighbours(source, dest, weight)
      if @distance[dest] > (weight + @distance[source])
        @distance[dest] = weight + @distance[source]
        @parent[dest] = source
      end
    end

    def algorithm_recur(next_parent_list)
      next_neighbour_list = [] 
      for index in 0..next_parent_list.length-1
        temp_neighbours = @comms.identify_neighbours(next_parent_list[index])
        temp_neighbours.each_with_index do |(key, value), indexNew|
          next_neighbour_list.push(key)
          send_message(next_parent_list[index], key, value)
        end
      end
      @comms.sync_all
      if @termination_count < @comms.message_count
        @temp_count.push(@termination_count)
        @termination_count = @comms.message_count
        algorithm_recur(next_neighbour_list.uniq)
      end
    end

    algorithm_init(1, total_nodes)
    algorithm_recur([1])
  end

  def print_output
    puts "Total message count #{@comms.message_count}"
    puts "Total time taken    #{(@comms.total_time_taken - 1)}"
    #puts "Shortest Graph Path #{@parent}"
  end

  def main(total_nodes, input_file)
    @comms.setting_up_values(get_input(input_file))
    algorithm(total_nodes)
    print_output
  end
end

BellmanFord.new.main(4, "../build/graph4.txt")
BellmanFord.new.main(16, "../build/graph16.txt")
BellmanFord.new.main(32, "../build/graph32.txt")
BellmanFord.new.main(64, "../build/graph64.txt")
BellmanFord.new.main(128, "../build/graph128.txt")
BellmanFord.new.main(512, "../build/graph512.txt")
BellmanFord.new.main(1024, "../build/graph1024.txt")
#BellmanFord.new.main(4096, "../build/graph4096.txt")
