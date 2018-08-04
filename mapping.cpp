
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>

int test_mapped_file_ostream(size_t TOTAL_SIZE, size_t BLOCK_SIZE, size_t N)
{
    const std::string filename = "test_filemapping.dat";
    boost::interprocess::file_mapping::remove(filename.data());

    {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    file.seekp(static_cast<std::streamoff>(TOTAL_SIZE-1));
    file.write("", 1);
    }

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    {
        boost::interprocess::file_mapping fmap(filename.data(), boost::interprocess::read_write);
        boost::interprocess::mapped_region mreg(fmap, boost::interprocess::read_write);
        mreg.advise( boost::interprocess::mapped_region::advice_sequential );

        std::shared_ptr<std::streambuf> buf( new boost::iostreams::stream_buffer<boost::iostreams::array_sink>((char*)(mreg.get_address()), mreg.get_size()));
        std::ostream ostream( buf.get() );

        const std::vector<char> data(BLOCK_SIZE,1);

        start=std::chrono::system_clock::now();     
        for ( size_t i=0; i<N; i++ ) {
            ostream.write( data.data(), data.size() );
        }
        end=std::chrono::system_clock::now();       
    }

    auto total = end-start;
    std::cout << "test_mapped_file_ostream (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(total).count() << std::endl;

    return 0;
}

int test_mapped_file_stdcopy_n(size_t TOTAL_SIZE, size_t BLOCK_SIZE, size_t N)
{
    const std::string filename = "test_filemapping_stdcopy.dat";
    boost::interprocess::file_mapping::remove(filename.data());

    {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    file.seekp(static_cast<std::streamoff>(TOTAL_SIZE-1));
    file.write("", 1);
    }

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    {
        boost::interprocess::file_mapping fmap(filename.data(), boost::interprocess::read_write);
        boost::interprocess::mapped_region mreg(fmap, boost::interprocess::read_write);
        mreg.advise( boost::interprocess::mapped_region::advice_sequential );

        char* regptr = (char*)mreg.get_address();
        const std::vector<char> data(BLOCK_SIZE,1);

        start=std::chrono::system_clock::now();     
        for ( size_t i=0; i<N; i++ ) {
            std::copy_n( data.data(), data.size(), regptr );
            regptr += data.size();
        }
        end=std::chrono::system_clock::now();       
    }

    auto total = end-start;
    std::cout << "test_mapped_file_stdcopy_n (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(total).count() << std::endl;

    return 0;
}

int test_fstream_file(size_t TOTAL_SIZE, size_t BLOCK_SIZE, size_t N)
{
    const std::string filename = "test_fstream.dat";

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    {
        const std::vector<char> data(BLOCK_SIZE,1);
        std::ofstream file(filename, std::ios::binary | std::ios::trunc);
        start=std::chrono::system_clock::now();     
        for ( size_t i=0; i<N; i++ ) {
            file.write( data.data(), data.size() );
        }
        end=std::chrono::system_clock::now();       
    }
    auto total = end-start;
    std::cout << "test_fstream_file (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(total).count() << std::endl;

    return 0;
}

int main(int argc, char **argv)
{
    if ( argc != 2 ) {
        std::cout << "Usage: " << argv[0] << " <size of output file in gigabytes>" << std::endl;
        exit(1);
    }

    uint64_t totalsize = std::stoull(argv[1]);
    if (totalsize==0) {
        totalsize = 1;
    }

    const std::size_t GB = (uint64_t)1 << 30; 
    const std::size_t TOTAL_SIZE = totalsize << 30; 
    const std::size_t BLOCK_SIZE = (uint64_t)1 << 20;
    const std::size_t N = TOTAL_SIZE/BLOCK_SIZE;

    std::cout << "TOTAL_SIZE (GB)=" << TOTAL_SIZE/GB << std::endl;
    test_mapped_file_ostream(TOTAL_SIZE,BLOCK_SIZE,N);
    test_mapped_file_stdcopy_n(TOTAL_SIZE,BLOCK_SIZE,N);
    test_fstream_file(TOTAL_SIZE,BLOCK_SIZE,N);
    return 0;
}
