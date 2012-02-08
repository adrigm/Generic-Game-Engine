/**
 * Provides the GGE namespace includes for the GGE Core engine includes and
 * variables.
 *
 * @file include/GGE/Core.hpp
 * @author Ryan Lindeman
 * @date 20100710 - Initial Release
 * @date 20110118 - Added ConfigReader and StateManager includes.
 * @date 20110127 - Changed name from GGE.hpp to Core.hpp and moved to include
 * @date 20110218 - Added ConfigAsset to Core includes
 */
#ifndef   GGE_CORE_HPP_INCLUDED
#define   GGE_CORE_HPP_INCLUDED
 
/////////////////////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////////////////////
#include <GGE/Config.hpp>

// GGE Core includes
#include <GGE/Core/classes/App.hpp>
#include <GGE/Core/classes/AssetManager.hpp>
#include <GGE/Core/classes/SceneManager.hpp>
#include <GGE/Core/classes/ConfigReader.hpp>

#endif // GGE_CORE_HPP_INCLUDED

/**
 * @defgroup Core GGE Core module
 * The GGE Core module/library provides all basic classes used by all game
 * engines in the GGE collection of modules/libraries. Each game engine genre
 * will be built on top of the GGE Core module/library.
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
