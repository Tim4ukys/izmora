#ifndef __IZMORA_SAMPLING_HPP__
#define __IZMORA_SAMPLING_HPP__

/**
* TO-DO: 
* Добавить тип(хистограма, точки и т.д.)
* Добавить легенду(где будет подписана вся основная инфа, дисперсия и т.д.)
* 
* -------
* 
* Структура lua файла:
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
