#pragma once
#include <gePlatformUtility.h>
#include <gePrerequisitesUtil.h>
class RTSPlayer
{
public:
  RTSPlayer() = default;
  ~RTSPlayer();

private:
  /**
   * @brief 
   */
  unsigned int m_id;
  /**
   * @brief 
   */
  std::string name;
};

