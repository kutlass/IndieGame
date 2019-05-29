using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace JetEdit
{
    class JetObject
    {
        public JetObject()
        {
            XmlTextWriter writer = new XmlTextWriter("JetSettings.xml", null);
            writer.Formatting = Formatting.Indented;
            
            //
            // Levels section of game settings
            //
            writer.WriteStartElement("levels");
            // Level 6
            writer.WriteStartElement("level");
            writer.WriteAttributeString("Number", "6");
            // Game Object 1
            writer.WriteStartElement("Object");
            writer.WriteAttributeString("X Position", "41");
            writer.WriteAttributeString("Y Position", "82");
            writer.WriteEndElement(); // Game Object 1

            writer.WriteEndElement(); // level 6

            // Level 7
            writer.WriteStartElement("level");
            writer.WriteAttributeString("Number", "7");
            // Game Object 1
            writer.WriteStartElement("Object");
            writer.WriteAttributeString("X Position", "26");
            writer.WriteAttributeString("Y Position", "33");
            writer.WriteEndElement(); // Game Object 1

            writer.WriteEndElement(); // level 6

            writer.WriteEndElement();
            //writer.WriteFullEndElement();
            
            writer.Close();

        }
    }
}
