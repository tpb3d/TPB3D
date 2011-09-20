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
using System.Diagnostics;

using OpenTK.Graphics;
using OpenTK;

namespace OOGL
{
	public class FrameBuffer : IDisposable
	{
		public readonly uint handleFrameBuffer;
		public readonly uint handleTexture;
		public readonly uint handleDepth;
		
		public readonly int width;
		public readonly int height;
		
		public FrameBuffer(int width, int height)
		{		
			this.width = width;
			this.height = height;

			GL.GenTextures(1, out handleTexture);
			GL.BindTexture(TextureTarget.Texture2D, handleTexture);
			GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba8, width, height, 0, PixelFormat.Rgba, PixelType.UnsignedByte, IntPtr.Zero);
			GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int) TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int) TextureMagFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int) TextureWrapMode.ClampToBorder);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int) TextureWrapMode.ClampToBorder);

			GL.GenTextures(1, out handleDepth);
            GL.BindTexture(TextureTarget.Texture2D, handleDepth );
            GL.TexImage2D(TextureTarget.Texture2D, 0, (PixelInternalFormat) All.DepthComponent32, width, height, 0, PixelFormat.DepthComponent, PixelType.UnsignedInt, IntPtr.Zero);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int) TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int) TextureMagFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int) TextureWrapMode.ClampToBorder);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int) TextureWrapMode.ClampToBorder);
			
			GL.Ext.GenFramebuffers(1, out handleFrameBuffer);
			GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, handleFrameBuffer);
			GL.Ext.FramebufferTexture2D(FramebufferTarget.FramebufferExt, FramebufferAttachment.ColorAttachment0Ext, TextureTarget.Texture2D, handleTexture, 0);
			GL.Ext.FramebufferTexture2D(FramebufferTarget.FramebufferExt, FramebufferAttachment.DepthAttachmentExt, TextureTarget.Texture2D, handleDepth, 0);
			
			FramebufferErrorCode errorCode = GL.Ext.CheckFramebufferStatus(FramebufferTarget.FramebufferExt);

			if(errorCode != FramebufferErrorCode.FramebufferCompleteExt)
			{
				throw new Exception(string.Format("Framebuffer construction failed with error: {0}", errorCode));
			}
		}
		
		public void Use()
		{
			GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, this.handleFrameBuffer);
			GL.Viewport(0, 0, width, height);
		}
		
		public static void UseDefault(int viewportWidth, int viewportHeight)
		{
			GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, 0);
			GL.Viewport(0, 0, viewportWidth, viewportHeight);
		}
		
		public void Dispose()
		{
			uint value;
		
			value = this.handleFrameBuffer; GL.Ext.DeleteFramebuffers(1, ref value);
			value = this.handleDepth; GL.DeleteTextures(1, ref value);
			value = this.handleTexture; GL.DeleteTextures(1, ref value);
		}
		
		private Matrix4 viewMatrix;
		public Matrix4 ViewMatrix
		{
			get
			{
				return viewMatrix;
			}
			set
			{
				viewMatrix = value;
			}
		}
		
		private Matrix4 projectionMatrix;
		public Matrix4 ProjectionMatrix
		{
			get
			{
				return projectionMatrix;
			}
			set
			{
				projectionMatrix = value;
			}
		}
	}
}
