//    Copyright 2008 James P Michels III
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

using OpenTK;
using OpenTK.Graphics;

namespace Ms3dLoader
{
    //
    // Then come nNumMaterials times ms3d_material_t structs (sizeof(ms3d_material_t) == 361)
    //
    //typedef struct
    //{
    //    char            name[32];                           //
    //    float           ambient[4];                         //
    //    float           diffuse[4];                         //
    //    float           specular[4];                        //
    //    float           emissive[4];                        //
    //    float           shininess;                          // 0.0f - 128.0f
    //    float           transparency;                       // 0.0f - 1.0f
    //    char            mode;                               // 0, 1, 2 is unused now
    //    char            texture[128];                        // texture.bmp
    //    char            alphamap[128];                       // alpha.bmp
    //} ms3d_material_t;
    public struct Material
    {
        public readonly string name;
        public readonly Vector4 ambient;
        public readonly Vector4 diffuse;
        public readonly Vector4 specular;
        public readonly Vector4 emissive;
        public readonly float shininess;
        public readonly float transparency;
        public readonly sbyte mode;
        public readonly string textureFile;
        public readonly string alphaMapFile;

        public Material(BinaryReader r)
        {
            name = ASCIIEncoding.ASCII.GetString(r.ReadBytes(32)).Split((char)0)[0];
            ambient = ReadColor(r);
            diffuse = ReadColor(r);
            specular = ReadColor(r);
            emissive = ReadColor(r);
            shininess = r.ReadSingle();
            transparency = r.ReadSingle();
            mode = r.ReadSByte();
            textureFile = ASCIIEncoding.ASCII.GetString(r.ReadBytes(128)).Split((char)0)[0];
            alphaMapFile = ASCIIEncoding.ASCII.GetString(r.ReadBytes(128)).Split((char)0)[0];
        }

        private static Vector4 ReadColor(BinaryReader reader)
        {
            float r = reader.ReadSingle();
            float g = reader.ReadSingle();
            float b = reader.ReadSingle();
            float a = reader.ReadSingle();

            return new Vector4(r, g, b, a);
        }

        public override string ToString()
        {
            return string.Format("Material name={0},ambient={1},diffuse={2},specular={3},emissive={4},shininess={5},transparency={6},mode={7},textureFile={8},alphaMapFile={9}", name, ambient, diffuse, specular, emissive, shininess, transparency, mode, textureFile, alphaMapFile);
        }

        public OOGL.Animation.Material GetOOGLMaterial(string ms3dFileName)
        {
            string relativeFileName = OOGL.ResourceLocator.GetFullPathRelative(ms3dFileName, this.textureFile);

            return new OOGL.Animation.Material
            (
                OOGL.Textures.TextureManager.Instance.Find(relativeFileName, TextureMagFilter.Nearest, TextureMinFilter.Nearest, TextureWrapMode.Repeat, TextureWrapMode.Repeat),
                this.ambient,
                this.diffuse,
                this.specular,
                this.emissive,
                this.shininess,
                this.transparency
            );
        }
    }
}

