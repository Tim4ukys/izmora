#include "main.hpp"

Sampling::Sampling(const std::string_view& file_name) : m_sampleName(file_name)
{
	sol::state lua;
	lua.open_libraries(sol::lib::math);
	lua.script_file(file_name.data());

	// загрузка информации о графике
	auto db_info = lua.get<sol::table>("db_info");
	m_dbInfo.m_name = db_info["name"].get<std::string>();
	
	auto tp_gr = db_info["type"].get<std::string>();
	if (tp_gr == "line") {
		m_dbInfo.m_axis.first = db_info["axis"].get<sol::table>()[1].get<std::string>();
		m_dbInfo.m_axis.second = db_info["axis"].get<sol::table>()[2].get<std::string>();
		m_dbInfo.m_tp = dbInfo::type::line;

		struct cd {
			double x, y, err_x, err_y;
		};
		m_data = std::make_any<Coords>();
		auto coord = std::any_cast<Coords>(&m_data);

		auto db = lua.get<sol::table>("db");
		coord->resize(db.size() + 1);
		for (auto& [i, coord_info] : db) {
			auto cd_inf = coord_info.as<sol::table>();
			auto k = i.as<size_t>();
			coord->getX()[k] = cd_inf["x"].get<double>();
			coord->getXErr()[k] = cd_inf["err_x"].get<double>();
			coord->getY()[k] = cd_inf["y"].get<double>();
			coord->getYErr()[k] = cd_inf["err_y"].get<double>();
		}
	}
	else if (tp_gr == "hist") {
		m_dbInfo.m_tp = dbInfo::type::hist;

		m_data = std::make_any<std::vector<double>>();
		auto arr = std::any_cast<std::vector<double>>(&m_data);
		auto db = lua.get<sol::table>("db");

		arr->resize(db.size());
		for (auto& [k, n] : db) {
			arr->at(k.as<size_t>() - 1) = n.as<double>();
		}
	}
}

void Sampling::draw()
{
	if (ImPlot::BeginPlot(m_dbInfo.m_name.c_str(), {-1, -1})) {
		if (m_dbInfo.m_tp == dbInfo::type::line) {
			auto coord = std::any_cast<Coords>(&m_data);
			ImPlot::SetupAxes(m_dbInfo.m_axis.first.c_str(), m_dbInfo.m_axis.second.c_str());
			ImPlot::PlotErrorBars("##line", coord->getX().data(), coord->getY().data(),
				coord->getXErr().data(),
				static_cast<int>(coord->getX().size()));
			ImPlot::PlotErrorBars("##line", coord->getX().data(), coord->getY().data(),
				coord->getYErr().data(),
				static_cast<int>(coord->getX().size()), ImPlotErrorBarsFlags_Horizontal);
			ImPlot::PlotLine("##line", coord->getX().data(), coord->getY().data(),
				static_cast<int>(coord->getX().size()));
			ImPlot::EndPlot();
		}
		else if (m_dbInfo.m_tp == dbInfo::type::hist) {
			auto arr = std::any_cast<std::vector<double>>(&m_data);
			ImPlot::PlotHistogram("##hist", arr->data(), arr->size());
			
			ImPlot::EndPlot();
		}
	}
}
