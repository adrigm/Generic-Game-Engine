/**
 * Provides the Font Asset type used by the AssetManager in the BGE namespace
 * which is responsible for providing the Asset management facilities for the
 * App base class used in the BGE core library.
 *
 * @file src/BGE/Core/assets/FontAsset.cpp
 * @author Ryan Lindeman
 * @date 20100724 - Initial Release
 * @date 20110127 - Moved to BGE Core library and src directory
 * @date 20110218 - Change to system include style
 * @date 20110611 - Convert logging to new Log macros
 * @date 20110627 - Removed extra ; from namespace
 */
 
#include <assert.h>
#include <stddef.h>
#include <BGE/Core/classes/App.hpp>
#include <BGE/Core/assets/FontAsset.hpp>
 
namespace BGE
{
  FontAsset::FontAsset(std::string theFilename, AssetLoadingStyle theStyle) :
    TAsset<sf::Font>(theFilename, theStyle)
  {
  }
 
  FontAsset::~FontAsset()
  {
    UnloadAsset();
  }
 
  void FontAsset::LoadAsset(void)
  {
    // Only load the asset once if possible!
    if(false == mLoaded)
    {
      // Make sure memory is not already allocated
      assert(NULL == mAsset && "FontAsset::LoadAsset() memory already allocated!");
 
      // Create the asset
      mAsset = new(std::nothrow) sf::Font;
      assert(NULL != mAsset && "FontAsset::LoadAsset() unable to allocate memory");
 
      mApp->log << "FontAsset::LoadAsset(" << mFilename << ") loading..." << std::endl;
 
      // Attempt to load the asset from a file
      mLoaded = mAsset->LoadFromFile(mFilename);
 
      // If the asset did not load successfully, delete the memory
      if(false == mLoaded)
      {
        mApp->log << "ERROR: " << "FontAsset::LoadAsset(" << mFilename << ") is missing" << std::endl;
      }
    }
  }
 
  void FontAsset::UnloadAsset(void)
  {
    // Delete the asset, forcing it to be removed from memory
    delete mAsset;
    mAsset = NULL;
    mLoaded = false;
  }
 
} // namespace BGE

/**
 * Copyright (c) 2010-2011 Ryan Lindeman
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
