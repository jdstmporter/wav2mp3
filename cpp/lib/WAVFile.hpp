/*
 * WAVFile.hpp
 *
 *  Created on: 30 Nov 2017
 *      Author: julianporter
 */

#ifndef DEBUG_WAVFILE_HPP_
#define DEBUG_WAVFILE_HPP_

#include <vector>
#include "PCMFile.hpp"
#include "enums.hpp"
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "Iterator32.hpp"



class WAVFile : public PCMFile {
friend std::ostream & operator << (std::ostream &o,const WAVFile &w);
protected:
	enum class DataFormat : uint16_t {
		PCM = 1,
		IEEEFloat = 3,
		ALaw = 6,
		ULaw = 7
	};
private:
	Iterator32::data_t file;
	std::pair<long,long> clip();
	void parseHeader();
	
protected:
	unsigned nBytes;
	unsigned bitsPerSample;
	unsigned dataSize;
	
	DataFormat format;
	static DataFormat convertFormat(const uint16_t);
public:
	
	WAVFile(const Iterator32::data_t &file_);
	WAVFile(std::ifstream & stream);
	
	
	//WAVFile(const Mode & mode_,const SampleRate & rate_,int sampleSize) : PCMFile(mode_,rate_,sampleSize) {};
	virtual ~WAVFile() = default;

	
	virtual PCMFile::Data bytes(); // Gives interleaved data
	
	
};
std::ifstream & operator >> (std::ifstream &i,WAVFile &w);
std::ostream & operator << (std::ostream &o,const WAVFile &w);

#endif /* DEBUG_WAVFILE_HPP_ */
