#include <cassert>
#include <sstream>
#include <BGE/Core/classes/App.hpp>
#include <BGE/Core/classes/StatManager.hpp>
 
namespace BGE
{
  StatManager::StatManager() :
    app(NULL),
    mShow(false),
    mFrames(0),
    mUpdates(0),
    mFPS(),
    mUPS()
  {
  }
 
  StatManager::~StatManager()
  {
    // Output to log file
    if(NULL != app)
    {
      app->log << "StatManager::~StatManager() dtor called" << std::endl;
    }
 
    // Clear pointers we don't need anymore
    app = NULL;
  }

  void StatManager::DoInit(void)
  {
    // Reset our counters
    mFrames = 0;
    mUpdates = 0;

    // Reset our clocks
    mFrameClock.Reset();
    mUpdateClock.Reset();

    // Position and color for the FPS/UPS string
    mFPS.SetColor(sf::Color(255,255,255,128));
    mFPS.Move(0,0);
    mUPS.SetColor(sf::Color(255,255,255,128));
    mUPS.Move(0,30);

    // Default strings to display for Frames/Updates per second
    mFPS.SetText("");
    mUPS.SetText("");
  }

  void StatManager::DeInit(void)
  {
  }

  bool StatManager::IsShowing(void) const
  {
    return mShow;
  }

  void StatManager::SetShow(bool theShow)
  {
    mShow = theShow;
  }

  uint32_t StatManager::GetUpdates(void) const
  {
    return mUpdates;
  }

  uint32_t StatManager::GetFrames(void) const
  {
    return mFrames;
  }

  void StatManager::RegisterApp(App* theApp)
  {
    // Check that our pointer is good
    assert(NULL != theApp && "StatManager::RegisterApp() theApp pointer provided is bad");
 
    // Make a note of the pointer
    assert(NULL == app && "StatManager::RegisterApp() theApp pointer was already registered");
    app = theApp;
  }

  void StatManager::Update(void)
  {
    // Check our App pointer
    assert(NULL != app && "StatManager::Update() bad app pointer");

    // Increment our update counter
    mUpdates++;
    if(mUpdateClock.GetElapsedTime() > 1.0f)
    {
      // Updates string stream
      std::ostringstream updates;

      // Update our UPS string to be displayed
      updates.precision(2);
      updates.width(7);
      updates << "UPS: " << std::fixed << (float)mUpdates / mUpdateClock.GetElapsedTime();
      mUPS.SetText(updates.str());

      // Reset our Update clock and update counter
      mUpdates = 0;
      mUpdateClock.Reset();
    }
  }

  void StatManager::Draw(void)
  {
    // Check our app pointer
    assert(NULL != app && "StatManager::Draw() invalid app pointer provided");

    // Increment our frame counter
    mFrames++;
    if(mFrameClock.GetElapsedTime() > 1.0f)
    {
      // Frames string stream
      std::ostringstream frames;

      // Get our FramesPerSecond value
      frames.precision(2);
      frames.width(7);
      frames << "FPS: " << std::fixed << (float)mFrames / mFrameClock.GetElapsedTime();
      mFPS.SetText(frames.str());

      // Reset our Frames clock and frame counter
      mFrames = 0;
      mFrameClock.Reset();
    }

    // Are we showing the current statistics?
    if(mShow)
    {
      // Draw the Frames Per Second debug value on the screen
      app->window.Draw(mFPS);

      // Draw the Updates Per Second debug value on the screen
      app->window.Draw(mUPS);
    }
  }
}; // namespace BGE
