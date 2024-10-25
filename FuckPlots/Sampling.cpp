#include "main.hpp"

Sampling::Sampling(const std::string_view& file_name) : m_sampleName(file_name)
{
	sol::state lua;
	lua.open_libraries(sol::lib::math);
	lua.script_file(file_name.data());
	struct cd {
		double x, y, err_x, err_y;
	};

	auto db = lua.get<sol::table>("db");
	m_coord.resize(db.size()+1);
	for (auto& [i, coord_info] : db) {
		auto cd_inf = coord_info.as<sol::table>();
		auto k = i.as<size_t>();
		m_coord.getX()[k] = cd_inf["x"].get<double>();
		m_coord.getXErr()[k] = cd_inf["err_x"].get<double>();
		m_coord.getY()[k] = cd_inf["y"].get<double>();
		m_coord.getYErr()[k] = cd_inf["err_y"].get<double>();
	}
}

void Sampling::draw()
{
	if (ImPlot::BeginPlot(m_sampleName.c_str(), {-1, -1})) {
		ImPlot::PlotErrorBars("##line", m_coord.getX().data(), m_coord.getY().data(),
			m_coord.getXErr().data(),
			static_cast<int>(m_coord.getX().size()));
		ImPlot::PlotErrorBars("##line", m_coord.getX().data(), m_coord.getY().data(),
			m_coord.getYErr().data(),
			static_cast<int>(m_coord.getX().size()), ImPlotErrorBarsFlags_Horizontal);
		ImPlot::PlotLine("##line", m_coord.getX().data(), m_coord.getY().data(), 
			static_cast<int>(m_coord.getX().size()) );
		ImPlot::EndPlot();
	}
}
