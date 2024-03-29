/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_WIDGET_SAVER_HPP
#define TGUI_WIDGET_SAVER_HPP


#include <TGUI/Loading/WidgetConverter.hpp>
#include <TGUI/Loading/DataIO.hpp>
#include <TGUI/Container.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Class to save widgets to a text file
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API WidgetSaver
    {
    public:
        using SaveFunction = std::function<std::shared_ptr<DataIO::Node>(WidgetConverter)>;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Save a container and its child widgets to a stream
        ///
        /// @param widget  The container to save
        /// @param stream  Stream to which the widget file will be written to
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void save(Container::Ptr widget, std::stringstream& stream);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the save function for a certain widget type
        ///
        /// @param type         Type of the widget
        /// @param saveFunction New save function
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void setSaveFunction(const std::string& type, const SaveFunction& saveFunction);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve the save function of a certain widget type
        ///
        /// @param type  Type of the widget
        ///
        /// @return Function called to save the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static const SaveFunction& getSaveFunction(const std::string& type);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        static std::map<std::string, SaveFunction> m_saveFunctions;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_WIDGET_SAVER_HPP
