#ifndef   STAT_MANAGER_H
#define   STAT_MANAGER_H

#include <stdint.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <BGE/Core/Core_types.hpp>
 
namespace BGE
{
  class StatManager
  {
  public:
 
    /**
     * StatManager constructor
     */
    StatManager();
 
    /**
     * StatManager deconstructor
     */
    virtual ~StatManager();
 
    /**
     * DoInit will reset all the statistics, load necessary fonts and
     * performing other useful things.
     */
    void DoInit(void);

    /**
     * DeInit will unload the fonts used and dump a summary of statistics
     * collected to the log file.
     */
    void DeInit(void);

    /**
     * IsShowing will return true if the current statistics are being displayed.
     * @return true if stats are being displayed, false otherwise
     */
    bool IsShowing(void) const;

    /**
     * SetShowing will either enable or disable the showing of the current
     * statistics being displayed.
     * @param[in] theShow is the new show value
     */
    void SetShow(bool theShow);

    /**
     * GetUpdate will return the current update number which is the number of
     * updates that have been called since the application started.
     * @return the number of updates since the application started.
     */
    uint32_t GetUpdates(void) const;

    /**
     * GetFrame will return the current frame number which is the number of
     * frames that have been displayed since the application started.
     * @return the number of frames since the application started.
     */
    uint32_t GetFrames(void) const;

    /**
     * RegisterApp will register a pointer to the App class so it can be used
     * by the StatManager for error handling and log reporting.
     * @param[in] theApp is a pointer to the App (or App derived) class
     */
    void RegisterApp(App* theApp);

    /**
     * Update is responsible for updating game loop statistics like Updates
     * per second.
     */
    void Update(void);
 
    /**
     * Draw is responsible for updating game loop statistics like Frames
     * per second and handling all Drawing needs for the StatManager.
     */
    void Draw(void);

  private:
    // Constants
    ///////////////////////////////////////////////////////////////////////////
 
    // Variables
    ///////////////////////////////////////////////////////////////////////////
    /// Pointer to the App class for error handling and logging
    App*        app;
    /// Allow the current statistics to be displayed?
    bool        mShow;
    /// Total number of frames drawn since DoInit was called
    uint32_t    mFrames;
    /// Frame clock for displaying Frames per second value
    sf::Clock   mFrameClock;
    /// Debug string to display that shows the frames per second
    sf::String  mFPS;
    /// Total number of updates done since DoInit was called
    uint32_t    mUpdates;
    /// Update clock for displaying Updates per second value
    sf::Clock   mUpdateClock;
    /// Debug string to display that shows the updates per second
    sf::String  mUPS;
 
    /**
     * StatManager copy constructor is private because we do not allow copies
     * of our class
     */
    StatManager(const StatManager&); // Intentionally undefined
 
    /**
     * Our assignment operator is private because we do not allow copies
     * of our class
     */
    StatManager& operator=(const StatManager&); // Intentionally undefined
 
  }; // class StatManager
}; // namespace BGE
 
#endif // STAT_MANAGER_H
