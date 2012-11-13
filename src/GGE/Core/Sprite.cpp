////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <GGE/Core/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>


namespace GGE
{
////////////////////////////////////////////////////////////
Sprite::Sprite() :
m_texture    (NULL),
m_textureRect()
{
}


////////////////////////////////////////////////////////////
Sprite::Sprite(const sf::Texture& texture) :
m_texture    (NULL),
m_textureRect()
{
    setTexture(texture);
}


////////////////////////////////////////////////////////////
Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rectangle) :
m_texture    (NULL),
m_textureRect()
{
    setTexture(texture);
    setTextureRect(rectangle);
}


////////////////////////////////////////////////////////////
void Sprite::setTexture(const sf::Texture& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no valid texture & rect before
    if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
        setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

    // Assign the new texture
    m_texture = &texture;
}


////////////////////////////////////////////////////////////
void Sprite::setTextureRect(const sf::IntRect& rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}


////////////////////////////////////////////////////////////
void Sprite::setColor(const sf::Color& color)
{
    // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}


////////////////////////////////////////////////////////////
const sf::Texture* Sprite::getTexture() const
{
    return m_texture;
}


////////////////////////////////////////////////////////////
const sf::IntRect& Sprite::getTextureRect() const
{
    return m_textureRect;
}


////////////////////////////////////////////////////////////
const sf::Color& Sprite::getColor() const
{
    return m_vertices[0].color;
}


////////////////////////////////////////////////////////////
sf::FloatRect Sprite::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}


////////////////////////////////////////////////////////////
sf::FloatRect Sprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////
void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_texture)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}


////////////////////////////////////////////////////////////
void Sprite::updatePositions()
{
    sf::FloatRect bounds = getLocalBounds();

    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(0, bounds.height);
    m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
    m_vertices[3].position = sf::Vector2f(bounds.width, 0);
}


////////////////////////////////////////////////////////////
void Sprite::updateTexCoords()
{
    float left   = static_cast<float>(m_textureRect.left);
    float right  = left + m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    m_vertices[3].texCoords = sf::Vector2f(right, top);
}

} // namespace sf
