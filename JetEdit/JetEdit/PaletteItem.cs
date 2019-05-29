using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace JetEdit
{
    public class PaletteItem
    {
        public string name;
        public Rectangle rectangle;
        public enum PaletteType
        {
            Player = 0,
            Enemy,
            Weapon,
            Powerup,
            Terrain
        }
        private PaletteType paletteType;

        //
        // Constructors
        //
        private PaletteItem() { }
        public PaletteItem(string name, Rectangle rectangle)
        {
            this.name = name;
            this.rectangle = rectangle;
            this.paletteType = PaletteType.Terrain; // Default to terrain, as it will be the most common level editing type
        }

        //
        // Public methods
        //
        // Override ToString so the ListBox databinding displays an intuitive name per object
        public override string ToString()
        {
            return this.name;
        }

        //
        // Properties
        //
        public PaletteType paletteTypeEnum
        {
            get { return this.paletteType; }
            set { this.paletteType = value; }
        }
    }
}
