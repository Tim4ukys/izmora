#ifndef __IZMORA_SAMPLING_HPP__
#define __IZMORA_SAMPLING_HPP__

/**
* TO-DO: 
* �������� ���(����������, ����� � �.�.)
* �������� �������(��� ����� ��������� ��� �������� ����, ��������� � �.�.)
* 
* -------
* 
* ��������� lua �����:
* db - table {double: double}
*/

class Sampling {
	Sampling() = delete;
	Coords m_coord;
	std::string m_sampleName;
public:
	explicit Sampling(const std::string_view& file_name);

	void draw();
};

#endif
