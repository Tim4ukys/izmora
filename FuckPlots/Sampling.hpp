#ifndef __IZMORA_SAMPLING_HPP__
#define __IZMORA_SAMPLING_HPP__

/**
* TO-DO: 
* Добавить тип(хистограма, точки и т.д.)
* Добавить возможность строить логарифмический график
* Добавить легенду(где будет подписана вся основная инфа, дисперсия и т.д.)
* 
* -------
* 
* Структура lua файла:
* db - table {{x, y, x_err, y_err}, ...}
* db_info - table {["name"] = "", ["axis"] = {"напруга", "время"}} 
*/

class Sampling {
	Sampling() = delete;
	std::any m_data;
	std::string m_sampleName;
	struct dbInfo {
		std::string m_name;
		enum class type { line, hist } m_tp;
		std::pair<std::string, std::string> m_axis;
	} m_dbInfo;
public:
	explicit Sampling(const std::string_view& file_name);

	void draw();
};

#endif
