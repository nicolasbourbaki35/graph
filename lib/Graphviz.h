#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <sstream>
#include <ostream>

namespace GraphLib
{

struct Node 
{
    enum Shape
    {
        Box,
        Polygon,
        Ellipse,
        Oval,
        Circle,
        Point,
        Egg,
        Triangle,
        Rectangle,
        Square,
        Star,
        None
    };
    
    static const char * shapeToString(Shape const & shape)
    {
        switch(shape)
        {
            case Box: 
                return "box";
            case Polygon:
                return "polygon";
            case Ellipse:
                return "ellips";
            case Oval:
                return "oval";
            case Circle:
                return "circle";
            case Point:
                return "point";
            case Egg:
                return "egg";
            case Triangle:
                return "triangle";
            case Rectangle:
                return "rectangle";
            case Square:
                return "square";
            case Star:
                return "star";
            case None:
                return "none";
            default:
                return "none";
        };
    }
};

struct Arrow
{
    enum Shape
    { 
        Box,
        Crow,
        Curve,
        Icurve,
        Diamond,
        Dot,
        Inv,
        None,
        Normal,
        Tee,
        Vee
    };

    static const char * shapeToString(Shape const & shape)
    {
        switch(shape)
        {
            case Shape::Box:
                return "box";
            case Shape::Crow:
                return "crow";
            case Shape::Curve:
                return "curve";
            case Shape::Icurve:
                return "icurve";
            case Shape::Diamond:
                return "diamond";
            case Shape::Dot:
                return "dot";
            case Shape::Inv:
                return "inv";
            case Shape::None:
                return "none";
            case Shape::Normal:
                return "normal";
            case Shape::Tee:
                return "tee";
            case Shape::Vee:
                return "vee";
            default:
                return "none";
        };
    }
};

class RGBColor
{
public:
    RGBColor( unsigned char red
            , unsigned char green
            , unsigned char blue
            , unsigned char alpha)
        : m_Red(red)
        , m_Green(green)
        , m_Blue(blue)
        , m_Alpha(alpha)
    {}
    
    unsigned char getRed()   const { return m_Red;   }
    unsigned char getGreen() const { return m_Green; }
    unsigned char getBlue()  const { return m_Blue;  }
    unsigned char getAlpha() const { return m_Alpha; }

    std::string toString() const 
    {
        std::ostringstream oss;
        return oss.str();
    }

private:
    unsigned char m_Red;
    unsigned char m_Green;
    unsigned char m_Blue;
    unsigned char m_Alpha;
};

/*
 * This simple processor can be used in graph trversal algorithm
 * in order to output it in Dot format
 */
template <typename EdgeType>
class GraphvizEdgeProcessor
{
public:
    GraphvizEdgeProcessor ( std::ostream & os,
        Node::Shape  const & node_shape  = Node::Shape::Circle,
        RGBColor     const & node_color  = RGBColor(255,255,255,0),
        Arrow::Shape const & arrow_shape = Arrow::Shape::Normal,
        RGBColor     const & arrow_color = RGBColor(255,255,255,0)) 
            : m_stream(os) 
            , m_node_shape(node_shape)
            , m_node_color(node_color)
            , m_arrow_shape(arrow_shape)
            , m_arrow_color(arrow_color)
    {
    }

    void operator()(EdgeType const & edge)
    {
        m_stream    << "\t \"" << edge.getSource() 
                    << "\" -> \"" << edge.getDestination()
                    << "\" [";

        if (edge.getWeight()!=0)
        {
            m_stream << "label=\"" << edge.getWeight() << "\"";
        }
        
        m_stream <<  "]" << std::endl;  
    } 

private:
    std::ostream & m_stream;
    Node::Shape    m_node_shape;
    RGBColor       m_node_color;
    Arrow::Shape   m_arrow_shape;
    RGBColor       m_arrow_color;
};

}

#endif

