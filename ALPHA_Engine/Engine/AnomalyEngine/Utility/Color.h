#pragma once

#include <array>
#include <algorithm>
#include <cstdint>

namespace AnomalyEngine {
    /**
     * @class Color
     * @brief Represents an RGBA color with 8-bit channels.
     *
     * Provides basic arithmetic operations, clamping, and normalization
     * for use in rendering, materials, and shaders.
     */
    class Color {
    public:
        uint8_t r; ///< Red channel (0–255)
        uint8_t g; ///< Green channel (0–255)
        uint8_t b; ///< Blue channel (0–255)
        uint8_t a; ///< Alpha channel (0–255)

    public:
        /**
         * @brief Default constructor. Initializes color to opaque white (255, 255, 255, 255).
         */
        constexpr Color() noexcept
            : r(255), g(255), b(255), a(255) {
        }

        /**
         * @brief Constructs a color from RGBA values.
         * @param red   Red component (0–255)
         * @param green Green component (0–255)
         * @param blue  Blue component (0–255)
         * @param alpha Alpha component (0–255, default 255)
         */
        constexpr Color(int red, int green, int blue, int alpha = 255) noexcept
            : r(static_cast<uint8_t>(std::clamp(red, 0, 255))),
            g(static_cast<uint8_t>(std::clamp(green, 0, 255))),
            b(static_cast<uint8_t>(std::clamp(blue, 0, 255))),
            a(static_cast<uint8_t>(std::clamp(alpha, 0, 255))) {
        }

        /**
         * @brief Constructs a color from normalized floats (0.0f–1.0f).
         */
        constexpr Color(float red, float green, float blue, float alpha = 1.0f) noexcept
            : r(static_cast<uint8_t>(std::clamp(red, 0.0f, 1.0f) * 255.0f)),
            g(static_cast<uint8_t>(std::clamp(green, 0.0f, 1.0f) * 255.0f)),
            b(static_cast<uint8_t>(std::clamp(blue, 0.0f, 1.0f) * 255.0f)),
            a(static_cast<uint8_t>(std::clamp(alpha, 0.0f, 1.0f) * 255.0f)) {
        }

        /**
         * @brief Returns the color as a normalized float array.
         * @return Array of 4 floats in [0.0f, 1.0f].
         */
        constexpr std::array<float, 4> ToFloatArray() const noexcept {
            return {
                r / 255.0f,
                g / 255.0f,
                b / 255.0f,
                a / 255.0f
            };
        }

        /**
         * @brief Linearly interpolates between two colors.
         * @param other Target color.
         * @param t Interpolation factor [0,1].
         * @return Interpolated color.
         */
        constexpr Color Lerp(const Color& other, float t) const noexcept {
            t = std::clamp(t, 0.0f, 1.0f);
            return Color(
                static_cast<uint8_t>(r + (other.r - r) * t),
                static_cast<uint8_t>(g + (other.g - g) * t),
                static_cast<uint8_t>(b + (other.b - b) * t),
                static_cast<uint8_t>(a + (other.a - a) * t)
            );
        }

        /**
         * @brief Multiplies color intensity by scalar (modifies RGB only).
         * @param value Multiplier in range [0.0f, ∞).
         */
        constexpr void Multiply(float value) noexcept {
            r = static_cast<uint8_t>(std::clamp(r * value, 0.0f, 255.0f));
            g = static_cast<uint8_t>(std::clamp(g * value, 0.0f, 255.0f));
            b = static_cast<uint8_t>(std::clamp(b * value, 0.0f, 255.0f));
        }

        /// Equality operator.
        constexpr bool operator==(const Color& other) const noexcept {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        /// Inequality operator.
        constexpr bool operator!=(const Color& other) const noexcept {
            return !(*this == other);
        }

        // --- Static predefined colors ---
        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
    };
}