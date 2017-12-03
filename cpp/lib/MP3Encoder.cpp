/*
 * MP3Encoder.cpp
 *
 *  Created on: 30 Nov 2017
 *      Author: julianporter
 */

#include "MP3Encoder.hpp"
#include <algorithm>
#include <stdexcept>



unsigned MP3Encoder::mp3SizeCalc(unsigned n) {
	return unsigned((double)n*1.25+7200.0);
}


MP3Encoder::MP3Encoder(PCMFile *data_,const unsigned quality,const unsigned rate) :
	data(data_), nSamples(data->samplesPerChannel()), mp3Size(MP3Encoder::mp3SizeCalc(nSamples)) {
		
	gf = lame_init();
	if(gf==nullptr) throw MP3Error("Cannot initialise LAME transcoder");
	lame_set_num_channels(gf,data->nChans());
	lame_set_in_samplerate(gf,data->samplesPerSecond());
	lame_set_brate(gf,rate);
	lame_set_mode(gf,data->mp3Mode());
	lame_set_quality(gf,quality);
		
	auto response=lame_init_params(gf);
	if(response<0) throw std::runtime_error("Cannot initialise LAME transcoder options");	
	
	mp3Out = new unsigned char[mp3Size];
}
	
MP3Encoder::~MP3Encoder() {
	lame_close(gf);
	delete[] mp3Out;
}	
	
void MP3Encoder::transcode() {
	try {
		auto d=data->bytes();
		std::shared_ptr<short int> pcmLeft=d.left;
		std::shared_ptr<short int> pcmRight=d.right;
		auto status=lame_encode_buffer(gf,pcmLeft.get(),pcmRight.get(),nSamples,mp3Out,mp3Size);
		if(status<0) throw MP3Error("Transcoding failed");
		mp3Size=status;
	}
	catch(MP3Error &e) { throw e; }
	catch(std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw MP3Error("Transcoding failed");
	}
}

std::ofstream & operator<<(std::ofstream &o,const MP3Encoder &e) {
	const unsigned char *u=e.mp3Out;
	const char *d=reinterpret_cast<const char *>(u);
	o.write(d,e.mp3Size);
	return o;
}
     