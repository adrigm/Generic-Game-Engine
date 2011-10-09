/**
 * Provides the BGE namespace includes for the BGE Core engine includes and
 * variables.
 *
 * @file include/BGE/Core.hpp
 * @author Ryan Lindeman
 * @date 20100710 - Initial Release
 * @date 20110118 - Added ConfigReader and StateManager includes.
 * @date 20110127 - Changed name from BGE.hpp to Core.hpp and moved to include
 * @date 20110218 - Added ConfigAsset to Core includes
 */
#ifndef   BGE_CORE_HPP_INCLUDED
#define   BGE_CORE_HPP_INCLUDED
 
/////////////////////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////////////////////
#include <BGE/Config.hpp>

// BGE Core includes
#include <BGE/Core/assets/ConfigAsset.hpp>
#include <BGE/Core/assets/FontAsset.hpp>
#include <BGE/Core/assets/ImageAsset.hpp>
#include <BGE/Core/assets/MusicAsset.hpp>
#include <BGE/Core/assets/SoundAsset.hpp>
#include <BGE/Core/classes/App.hpp>
#include <BGE/Core/classes/AssetManager.hpp>
#include <BGE/Core/classes/ConfigReader.hpp>
#include <BGE/Core/classes/tmx/Tmx.h>
#include <BGE/Core/classes/StatManager.hpp>
#include <BGE/Core/classes/SceneManager.hpp>
#include <BGE/Core/classes/TAsset.hpp>

#endif // BGE_CORE_HPP_INCLUDED

/**
 * @defgroup Core BGE Core module
 * The BGE Core module/library provides all basic classes used by all game
 * engines in the BGE collection of modules/libraries. Each game engine genre
 * will be built on top of the BGE Core module/library.
 *
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
