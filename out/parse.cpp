#include "config.pb.h"
#include <sys/types.h>   
#include <sys/stat.h>    
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

using namespace std;
void listFile(config::Config& cfg)
{
	for(int i = 0; i < cfg.camera_size(); ++i)
	{
		cout << "[" << i << "]:\n" <<endl;
		cout << "\tstore id: " << cfg.camera(i).store_id()<<endl;;
		cout << "\tcamera id: " << cfg.camera(i).camera_id()<<endl;;
		cout << "\tcamera ip: " << cfg.camera(i).ip_address()<<endl;;
		cout << "\tlog name: " << cfg.camera(i).name()<<endl;;
		cout << "\tlog password: " << cfg.camera(i).password()<<endl;;
		cout << "\tcamear desc: " << cfg.camera(i).desc()<<endl;;
		cout << "\tcamear settings:\n";
		cout << "\t\tglobal_head_detect_thresh: " << cfg.camera(i).settings().global_head_detect_thresh()<<endl;;
		cout << "\t\treef: " << cfg.camera(i).settings().reef().x() << "|" << cfg.camera(i).settings().reef().y()<<endl;;
		cout << "\t\tmask_path:" << cfg.camera(i).settings().mask_path()<<endl;;
		if(cfg.camera(i).settings().algorithm_mode() == config::Settings::SNAPSHOT)
			cout << "\t\talgorithm_mode:" << cfg.camera(i).settings().algorithm_mode()<<endl;;
	}	
}
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	const char* ptxt = "./config.prototxt";
 	config::Config cfg;	
	int fd = open(ptxt, O_RDONLY);
	if(fd == -1) cout << "File not found: " << ptxt;
	FileInputStream* input = new FileInputStream(fd);
	bool success = google::protobuf::TextFormat::Parse(input, &cfg);
	delete input;
	close(fd);
	if(success)
	{
		cout << "parse success!" << endl;
		listFile(cfg);
	}	
	return 0;
}
