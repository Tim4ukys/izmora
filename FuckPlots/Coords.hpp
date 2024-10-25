#ifndef __IZMORA_COORDS_HPP__
#define __IZMORA_COORDS_HPP__

class Coords {
    std::vector<double> m_pX, m_pY, m_aErrX, m_aErrY;
public:
    explicit Coords() = default;

    inline void resize(const size_t& len) { m_pX.resize(len); m_pY.resize(len); m_aErrX.resize(len); m_aErrY.resize(len); }
    auto& getX() noexcept { return m_pX; }
    auto& getXErr() noexcept { return m_aErrX; }
    auto& getY() noexcept { return m_pY; }
    auto& getYErr() noexcept { return m_aErrY; }
};

#endif
