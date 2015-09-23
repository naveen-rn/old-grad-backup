class FileRead
  def check_file_path(filePath)
  	File.exists?(filePath)
  end

  def check_file_avail(fileNameAndPath)
  	File.exists?(fileNameAndPath)
  end

  def read_file(fileNameAndPath)
  	file = File.open(fileNameAndPath)
  	fileContentList = Array.new
  	file.each_line do |line|
  	  line_list = Array.new
  	  line.split(",").each do |value|
  		line_list.push value.to_i
  	  end
  	  fileContentList.push line_list
  	end
  	fileContentList
  end

  def format_input(fileContentList)
    input = Hash.new {|hsh,key| hsh[key] = [] }
    (0..fileContentList.size-1).inject(0) do |result, index|
        input[fileContentList[index][0]].push [fileContentList[index][1], 
                                            fileContentList[index][2]]
    end
    input
  end
end
