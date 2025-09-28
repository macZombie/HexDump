# hexdump.tb



def formatHex(valueI,digits)
    
    valueS = valueI.to_s(16)
    
    outputString = ""


    for index in ( 1 .. digits - ( valueS.size )  )
         
         outputString = outputString + "0"
        
    end
    
    
    outputString = outputString + valueS
    
    return outputString
    
end





BEGIN { print "\nINFO: Start of ",$PROGRAM_NAME }


case(ARGV.size)
  
    when ( 0 )
        print "\nEnter input file name:- "
        inputFileName = gets.chomp.strip
    
    when ( 1 )
         inputFileName = ARGV[0]
        
    else
        print "\nERROR: Wrong number of arguments"
        print "\nUSAGE: ruby hexdump.rb filename.hex "
        Process.exit(0)
    
end  # case



if ( File.exist?(inputFileName) == false )
    
    print "\nERROR: The file named ",inputFileName," does not exist\n\n\n"
    
    Process.exit(0)
    
end




inputFile = File.new(inputFileName)

File.open inputFile,"rb"

fileSize = inputFile.size

print "\nINFO: The file named ",inputFileName," is ",fileSize," bytes long"


memory = Array.new( fileSize , 0   )



for index in ( 0 .. ( fileSize - 1 ) )
    
    dataS = inputFile.getc.encode!('UTF-8', 'binary', invalid: :replace, undef: :replace, replace: '')
    
    if ( dataS != "")
    
        data = dataS.ord

        memory[index] = data
        
    end
    
end



inputFile.close();


address = 0

begin

    print "\n",formatHex(address,4),"    "
    
    
    charBuffer = ""
    
    for inner in ( 0 .. 7 )

        dataS = memory[address + inner]

        dataD = dataS.to_i

        print formatHex(dataD,2), "  "
        

        if ( ( dataD >= 32 ) && ( dataD <= 126 ) )
            
            theChar = dataD.chr
            
        else
            
            theChar = "."
            
        end

        charBuffer = charBuffer + theChar
        
    end
    
    print "    ",charBuffer

    address = address + 8
    
end while ( address < fileSize )
    



END { print "\n\nINFO: End of ",$PROGRAM_NAME,"\n\n" }



