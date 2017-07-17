/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once
#include "ofxDatGuiTheme.h"

/*
    Stock Themes
*/

class ofxDatGuiThemeVMM : public ofxDatGuiTheme{

    public:
    
        ofxDatGuiThemeVMM()
        {
            stripe.visible = false;
            layout.matrix.buttonSize = 16;
            color.label = hex(0x6E6E6E);
            color.icons = hex(0x6E6E6E);
            color.background = hex(0xFCFAFD);
            color.guiBackground = hex(0xD8D8DB);
            color.inputAreaBackground = hex(0xE9E9E9);
            color.slider.fill = hex(0x6E6E6E);
            color.slider.text = hex(0x6E6E6E);
            color.textInput.text = hex(0x6E6E6E);
            color.textInput.highlight = hex(0xFCFAFD);
            color.colorPicker.border = hex(0xDFDDDF);
            color.textInput.backgroundOnActive = hex(0xD1D1D1);
            color.backgroundOnMouseOver = hex(0xECECEC);
            color.backgroundOnMouseDown = hex(0xDFDDDF);
            color.matrix.normal.button = hex(0xDFDDDF);
            color.matrix.hover.button = hex(0x9C9DA1);
            color.matrix.selected.button = hex(0x6E6E6E);
            color.pad2d.line = hex(0x6E6E6E);
            color.pad2d.ball = hex(0x6E6E6E);
            color.graph.fills = hex(0x6E6E6E);
            font.file = "ofxbraitsch/fonts/Verdana.ttf";
            
            //text input boxes. make em slim
            layout.height = 20;
            
            init();
        }
};




