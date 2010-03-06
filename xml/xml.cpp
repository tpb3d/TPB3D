#include "xml.h"

#include <iostream>

/*namespace OT {
    namespace xml {
        bool GetUIElements(TiXmlNode* ParentNode, std::vector<sf::Drawable*>& ToFill) {
            if (!ParentNode) return false;
            TiXmlElement* gfxnode = ParentNode->FirstChildElement();
            for (; gfxnode; gfxnode = gfxnode->NextSiblingElement()) {
                TiXmlNode* posnode = gfxnode->FirstChild("pos");
                sf::Vector2i pos = GetPointi(posnode);
                std::string Type = gfxnode->Value();
                if (Type == "img") {
                    TiXmlNode* file = gfxnode->FirstChild("file");
                    if (file) {
                        std::string filestr = file->FirstChild()->Value();
                        sf::Sprite* img = new sf::Sprite();
                        //img->SetImage(*Gfx::GetImage(filestr));
                        img->SetPosition(pos.x, pos.y);
                        ToFill.push_back(img);
                    } else {
                        std::cout << "WARNING: failed to load image, no file was specified!\n";
                    }
                } else if (Type == "text") {
                    TiXmlNode* value = gfxnode->FirstChild("value");
                    sf::String* str = new sf::String();
                    str->SetPosition(pos.x, pos.y);
                    sf::Vector2f sizev = GetPoint(gfxnode->FirstChild("size"));
                    float size = sizev.y-pos.y;
                    if (size > 0) {
                        str->SetSize(size);
                    }
                    if (value) {
                        std::string valuestr = value->FirstChild()->Value();
                        str->SetText(valuestr);
                    } else {
                        std::cout << "WARNING: No text was specified for <text> node.\n";
                    }
                    TiXmlNode* color = gfxnode->FirstChild("color");
                    str->SetColor(GetColor(color));
                    ToFill.push_back(str);
                } else if (Type == "shape") {
                    TiXmlNode* shapetypenode = gfxnode->FirstChild("type");
                    std::string ShapeType = "";
                    if (shapetypenode) {
                        ShapeType = shapetypenode->FirstChild()->Value();
                    }
                    if (ShapeType == "") {
                        TiXmlNode* pointnode = gfxnode->FirstChild("point");
                        sf::Shape* Shape = new sf::Shape();
                        for (; pointnode; pointnode = pointnode->NextSibling("point")) {
                            sf::Vector2f Point = GetPoint(pointnode->FirstChild("pos"));
                            TiXmlNode* fill = pointnode->FirstChild("fill");
                            sf::Color FillColor(255,255,255,255);
                            if (fill) {
                                FillColor = GetColor(fill->FirstChild("color"));
                            }
                            TiXmlNode* outline = pointnode->FirstChild("outline");
                            sf::Color OutlineColor(0,0,0,255);
                            //float Thikness = 1;
                            if (outline) {
                                OutlineColor = GetColor(outline->FirstChild("color"));
                                /*TiXmlNode* thikness = outline->FirstChild("thikness");
                                if (thikness) {
                                    Thikness = String::ToFloat(thikness->FirstChild()->ValueStr());
                                }*//*
                            }
                            Shape->AddPoint(Point, FillColor, OutlineColor);
                        }
                        ToFill.push_back(Shape);
                    } else {
                        TiXmlNode* sizenode = gfxnode->FirstChild("size");
                        sf::Vector2i size = GetPointi(sizenode);
                        size += pos;
                        TiXmlNode* outline = gfxnode->FirstChild("outline");
                        sf::Color OutlineColor(0,0,0,255);
                        float OutlineThikness = 2;
                        if (outline) {
                            OutlineColor = GetColor(outline->FirstChild("color"));
                            TiXmlNode* thikness = outline->FirstChild("thinkness");
                            if (thikness) {
                                OutlineThikness = String::ToFloat(thikness->FirstChild()->Value());
                            }
                        }
                        TiXmlNode* fill = gfxnode->FirstChild("fill");
                        sf::Color FillColor(255,255,255,255);
                        if (fill) {
                            FillColor = GetColor(fill->FirstChild("color"));
                        } else {
                            std::cout << "WARNING: Cannot find fill color node, defaulting to white.\n";
                        }

                        if (ShapeType == "rectangle") {

                            sf::Shape* rect = new sf::Shape();
                            std::cout << "creating rectangle at (" << pos.x << ", " << pos.y << ") with size (" << size.x << ", " << size.y
                                << ").\n";
                            *rect = sf::Shape::Rectangle(pos.x, pos.y, size.x, size.y, FillColor, OutlineThikness, OutlineColor);
                            rect->EnableFill(true);
                            std::cout << "rectangle created at ";
                            for (unsigned int i = 0; i <rect->GetNbPoints(); i++) {
                                std::cout << "(" << rect->GetPointPosition(i).x << ", " << rect->GetPointPosition(i).y << ")";
                            }
                            std::cout << '\n';
                            ToFill.push_back(rect);
                            continue;
                        } else if (ShapeType == "circle") {
                            sf::Vector2f Center;
                            Center.x = pos.x+((size.x-pos.x)/2);
                            Center.y = pos.y+((size.y-pos.y)/2);
                            float Radius = (size.x-pos.x)/2;
                            sf::Shape* circle = new sf::Shape();
                            *circle = sf::Shape::Circle(Center, Radius, FillColor, OutlineThikness, OutlineColor);
                            ToFill.push_back(circle);
                        } else {
                            std::cout << "WARNING: " << ShapeType << " is not a supported shape type, ignored.\n";
                        }
                    }

                } else {
                    std::cout << "WARNING: " << Type << " is not a supported node type, ignored.\n";
                }
            }
            return true;
        }
        sf::Color GetColor(TiXmlNode* ColorNode) {
            if (!ColorNode) {
                std::cout << "WARNING: NULL node passed to color parsing function, returning red.\n";
                return sf::Color(255,0,0,255);
            }
            TiXmlNode* rnode = ColorNode->FirstChild("r");
            TiXmlNode* gnode = ColorNode->FirstChild("g");
            TiXmlNode* bnode = ColorNode->FirstChild("b");
            TiXmlNode* anode = ColorNode->FirstChild("a");
            int r = 0;
            int g = 0;
            int b = 0;
            int a = 255;
            if (rnode) r = String::ToInt(rnode->FirstChild()->ValueStr());
            if (gnode) g = String::ToInt(gnode->FirstChild()->ValueStr());
            if (bnode) b = String::ToInt(bnode->FirstChild()->ValueStr());
            if (anode) a = String::ToInt(anode->FirstChild()->ValueStr());
            return sf::Color(r,g,b,a);
        }
        sf::Vector2i GetPointi(TiXmlNode* PointNode) {
            if (!PointNode) {
                std::cout << "WARNING: NULL node passed to point parsing function, returning (0,0)\n";
                return sf::Vector2i(0,0);
            }
            TiXmlNode* xnode = PointNode->FirstChild("x");
            TiXmlNode* ynode = PointNode->FirstChild("y");
            int x = 0;
            int y = 0;
            if (xnode) x = String::ToInt(xnode->FirstChild()->ValueStr());
            if (ynode) y = String::ToInt(ynode->FirstChild()->ValueStr());
            return sf::Vector2i(x,y);
        }
        sf::Vector2f GetPoint(TiXmlNode* PointNode) {
            if (!PointNode) {
                std::cout << "WARNING: NULL node passed to point parsing function, returning (0,0)\n";
                return sf::Vector2f(0,0);
            }
            TiXmlNode* xnode = PointNode->FirstChild("x");
            TiXmlNode* ynode = PointNode->FirstChild("y");
            float x = 0;
            float y = 0;
            if (xnode) x = String::ToFloat(xnode->FirstChild()->ValueStr());
            if (ynode) y = String::ToFloat(ynode->FirstChild()->ValueStr());
            return sf::Vector2f(x,y);
        }
    }
}*/
