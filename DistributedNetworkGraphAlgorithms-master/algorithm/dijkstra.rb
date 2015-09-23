require '../engine/src/comms'
require '../engine/src/file_read'

class Djikstra

  def initialize
  	@inputPath = "../build"
	  @inputFile = "../build/graph.txt"	
  	@source = Hash.new
  	@comms = Communication.new
    @next_neighbour = []
    @count = 0
  end

  def get_input(inputFile)
  	if FileRead.new.check_file_path(@inputPath)
  	  if FileRead.new.check_file_avail(inputFile)
  	  	@source = FileRead.new.format_input(FileRead.new.read_file(inputFile))
  	  end
  	end
  	@source
  end   

  def algorithm

    def send_message(source_id)
      temp_neighbours = @comms.identify_neighbours(source_id)
      temp_neighbours.each_with_index do |(key, value), index|
        @comms.send_message_to_neighbours(source_id, key, value)
      end
      temp_neighbours
    end
    
    def algorithm_recur(temp_neighbours)
      @comms.sync_all
      @next_neighbour = []
      uniq_neighbours = @comms.graph_covered
      temp_neighbours.each_with_index do |(key, value), index|
        if !(uniq_neighbours.include?(key))
          @comms.send_confirm_to_parents(key)
        end
          @next_neighbour.push(key) 
      end

      @comms.sync_all
      @comms.clear_intermediate_buffer
      temp_neighbours.each_with_index do |(key, value), index|
        if !(uniq_neighbours.include?(key))
          @comms.converge_cast(key)
        end
      end
      temp_neighbours.each_with_index do |(key, value), index|
        if !(uniq_neighbours.include?(key))
          @comms.form_tree(key)
        end
      end

      next_neighbour_list = @comms.find_next_neighbour(@next_neighbour)
      if next_neighbour_list.length != 0
        new_temp_neighbour = Hash.new {|hsh,key| hsh[key] = []}
        @next_neighbour = @next_neighbour - uniq_neighbours
        for index in 0..@next_neighbour.length-1
          if (@comms.individual_neighbour(@next_neighbour[index])).length != 0
            new_temp_neighbour = new_temp_neighbour.merge(send_message(@next_neighbour[index]))
          end
        end
        algorithm_recur(new_temp_neighbour)
      end

    end

    algorithm_recur(send_message(1))
  
  end

  def print_output
    puts "Total message count #{@comms.message_count}"
    puts "Total time taken    #{@comms.total_time_taken-2}"
    #puts "Shortest Graph Path #{@comms.graph_path_return}"
  end

  def main(inputFile)
    @comms.setting_up_values(get_input(inputFile))
    algorithm
    print_output
  end
end

Djikstra.new.main("../build/graph4.txt")
Djikstra.new.main("../build/graph16.txt")
Djikstra.new.main("../build/graph32.txt")
Djikstra.new.main("../build/graph64.txt")
Djikstra.new.main("../build/graph128.txt")
Djikstra.new.main("../build/graph512.txt")
Djikstra.new.main("../build/graph1024.txt")
Djikstra.new.main("../build/graph4096.txt")
