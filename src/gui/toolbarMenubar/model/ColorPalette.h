#pragma once

#include <map>
#include <string>
#include <vector>

#include <filesystem.h>
#include <util/NamedColor.h>

/**
 * @brief Header entity of a gpt file
 * This is simply a key value pair. The main reason to define a struct for this is to define a custom input operator.
 *
 */
struct Header {
    /**
     * @brief Input operator for parsing Header from input string stream
     *
     * @param str input string stream
     * @param header output for parsed Header
     * @return std::istream& which is the rest of the input string stream after parsing
     */
    friend std::istream& operator>>(std::istream& str, Header& header);

private:
    friend class Palette;
    /**
     * @brief Attribute name given in gpt file
     *
     */
    std::string attribute;

    /**
     * @brief Value for corresponding attribute in gpt file
     *
     */
    std::string value;

    /**
     * @brief Swap all properties between two Header instances
     *
     * @param other other Header instance to swap properties with
     */
    void swap(Header& other);
};

/**
 * @brief ColorPalette coming from a parsed gpt file
 *
 */
struct Palette {
    /**
     * @brief Construct a new Palette
     * This does not yet parse the file. It simply sets up the class.
     *
     * @param path to the gpt file
     */
    Palette(fs::path path);

    /**
     * @brief Create a default gpt file for the xournalpp color scheme
     * Default xournalpp color scheme
     *   0 0 0 Black
     *   0 128 0 Green
     *   0 192 255 Light Blue
     *   0 255 0 Light Green
     *   51 51 204 Blue
     *   128 128 128 Gray
     *   255 0 0 Red
     *   255 0 255 Magenta
     *   255 128 0 Orange
     *   255 255 0 Yellow
     *   255 255 255 White
     *
     * @param path to write gpt file to
     */
    static void create_default(fs::path path);

    /**
     * @brief Parse the gpt file in filepath
     * This fills the header map and the namedColors vector after clearing them first
     *
     */
    void load();

    /**
     * @brief Get the number of namedColors part of the palette
     *
     * @return size_t number of namedColors in palette
     */
    size_t size() const;

    /**
     * @brief Get a NamedColor from the palette
     *
     * @param i palette index
     * @return NamedColor of palette at palette index
     */
    NamedColor getColorAt(size_t i) const;

    /**
     * @brief Get the pointer to a NamedColor from the palette
     *
     * @param i palette index
     * @return NamedColor* pointer to a NamedColor from the palette
     */
    NamedColor* getColorPointerAt(size_t i);


private:
    /**
     * @brief filepath to the gpt file the palette is coming from
     *
     */
    fs::path filepath;

    /**
     * @brief Vector containing all colors of the palette
     *
     */
    std::vector<NamedColor> namedColors;

    /**
     * @brief Map containing the key value pairs of the gpt header
     * e.g. "Palette Name", "Description"
     *
     */
    std::map<std::string, std::string> header;

    /**
     * @brief Verify if line contains the expected "GIMP Palette" string
     *
     * @param line first line of gpt file
     * @return true if line is "GIMP Palette"
     * @return false otherwise
     */
    bool parseFirstGimpPaletteLine(const std::string& line);

    /**
     * @brief Try to parse a color and add it to namedColors
     *
     *
     * @param line line of gpt file
     * @return true if line is of form "255 255 255 White" (r g b name)
     * @return false otherwise
     */
    bool parseColorLine(const std::string& line);

    /**
     * @brief Try to parse a header key value pair and add it to header
     *
     * @param line line of gpt file
     * @return true if line is of form "key:value"
     * @return false otherwise
     */
    bool parseHeaderLine(const std::string& line);
};
