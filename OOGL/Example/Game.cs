// Copyright (C) 2008 James P Michels III
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;
using System.Threading;
using System.IO;

using OpenTK;
using OpenTK.Graphics;
using OpenTK.Input;
using OpenTK.Platform;

using OOGL.Animation;
using OOGL.Shaders;
using OOGL.Textures;
using OOGL;

using OOGL.GUI;
using OOGL.GUI.Abstract;
using OOGL.GUI.VertexStructures;

namespace Example
{
    class Game : GameWindow
    {
		private BaseFrameMgr frameMgr;
		private Model model;
        private Controller controller;

		private static Game game;
		public static Game Instance
		{
			get
			{
				return game;
			}
		}
				
        public Game()  
		{
			game = this;
				
			this.Width = 800;
			this.Height = 600;
			this.Title = "OOGL Example";
			
			this.VSync = VSyncMode.Off;
			
			ResourceLocator.RootPath = System.Environment.CurrentDirectory + "/../../../Media/";
			
			ShaderProgram positionColorShader = new ShaderProgram(ResourceLocator.GetFullPath("Shaders/guiColored.vs"), ResourceLocator.GetFullPath("Shaders/guiColored.fs"));
			ShaderProgram positionTextureShader = new ShaderProgram(ResourceLocator.GetFullPath("Shaders/guiTextured.vs"), ResourceLocator.GetFullPath("Shaders/guiTextured.fs"));
			
			this.frameMgr = new BaseFrameMgr(this, positionColorShader, positionTextureShader);

            this.Keyboard.KeyDown += new EventHandler<KeyboardKeyEventArgs>(Game_KeyDown);
            this.Keyboard.KeyUp += new EventHandler<KeyboardKeyEventArgs>(Game_KeyUp);

            this.Mouse.ButtonDown += new EventHandler<MouseButtonEventArgs>(Game_MouseDown);
            this.Mouse.ButtonUp += new EventHandler<MouseButtonEventArgs>(Game_MouseUp);
            this.Mouse.Move += new EventHandler<MouseMoveEventArgs>(Game_MouseMove);
            this.Mouse.WheelChanged += new EventHandler<MouseWheelEventArgs>(Game_WheelChanged);
									
			new DemoWindow(this.frameMgr);
			new PlayerWindow(this.frameMgr);
			new RadarWindow(this.frameMgr);
			new WaypointWindow(this.frameMgr);

            this.frameMgr.LoadWorkspace();
		
			Ms3dLoader.File ms3dFile = new Ms3dLoader.File(ResourceLocator.GetFullPath("Models/Beta_Kamujin/Beta_Kamujin.ms3d"));

            Sample[] tracks = Sample.Load(ResourceLocator.GetFullPath("Models/Beta_Kamujin/Beta_Kamujin.animations"));
			ShaderProgram modelShader = new ShaderProgram(ResourceLocator.GetFullPath("Shaders/skeletalAnimation.vs"), ResourceLocator.GetFullPath("Shaders/skeletalAnimation.fs"));
            this.model = ms3dFile.ToModel(modelShader, tracks);
            this.controller = new Controller(model);
		}


        protected override void OnLoad(EventArgs e)
        {
			base.OnLoad(e);
			
            GL.Enable(EnableCap.DepthTest);
			GL.DepthFunc(DepthFunction.Lequal);

			GL.CullFace(CullFaceMode.Back);
			GL.Enable(EnableCap.CullFace);
//			GL.Disable(EnableCap.CullFace);
			GL.Enable(EnableCap.Multisample);

			SetupLighting();
        }

        protected override void OnResize(EventArgs e)
        {
            Console.WriteLine(string.Format("Resizing ViewPort: width={0},height={1}", this.Width, this.Height));

            GL.Viewport(0, 0, this.Width, this.Height);

            float aspectRatio = this.Width / (float)this.Height;
			float fieldOfView = (float)Math.PI / 4.0f;
			
			this.projectionMatrix = Matrix4.Perspective(fieldOfView, aspectRatio, 1.0f, 1000.0f);

			GL.MatrixMode(MatrixMode.Projection);
			GL.LoadMatrix(Matrix4Helper.ToOpenGL(this.projectionMatrix));

            base.OnResize(e);
        }

		private void Game_MouseDown(object sender, MouseButtonEventArgs e)
        {
        	/* bool consumed = */ frameMgr.OnMouseDown(sender, e);
        }
        
        private void Game_MouseUp(object sender, MouseButtonEventArgs e)
        {
        	/* bool consumed = */ frameMgr.OnMouseUp(sender, e);
        }

		private void Game_MouseMove(object sender, MouseMoveEventArgs e)
		{			
            if (Mouse[MouseButton.Right])
            {
                if (e.XDelta != 0) cameraYaw += (e.XDelta * Functions.DTORF * 0.5f);
                if (e.YDelta != 0) cameraPitch += (e.YDelta * Functions.DTORF * 0.5f);
            }
            else
            {
                if (e.XDelta != 0 || e.YDelta != 0) 
				{
					/* bool consumed = */ frameMgr.OnMouseMove(sender, e);
				}
            }			
		}
		
		private void Game_WheelChanged(object sender, MouseWheelEventArgs e)
		{
			chaseDistance -= e.Delta;
		}

        //private void Game_KeyDown(KeyboardDevice keyboard, Key key)
        //{
        //    if (frameMgr.ConsumingKeyboard)
        //    {
        //        frameMgr.OnKeyDown(keyboard, key);
        //    }

        //    if (Keyboard[Key.Escape]) Exit();
        //    if (Keyboard[Key.F1]) SetPolygonMode(PolygonMode.Fill);
        //    if (Keyboard[Key.F2]) SetPolygonMode(PolygonMode.Line);
        //    if (Keyboard[Key.F3]) this.controller.CrossfadeTo("Battloid-Transport");
        //    if (Keyboard[Key.F4]) this.controller.CrossfadeTo("Transport-Battloid");
        //    if (Keyboard[Key.F5]) this.controller.CrossfadeTo("Run");

        //    if (Keyboard[Key.Home]) chaseDistance -= 1;
        //    if (Keyboard[Key.End]) chaseDistance += 1;				
        //}

        private void Game_KeyDown(object sender, KeyboardKeyEventArgs e) {
            if (frameMgr.ConsumingKeyboard) {
                frameMgr.OnKeyDown(sender, e);
            }

            if (Keyboard[Key.Escape]) Exit();
            if (Keyboard[Key.F1]) SetPolygonMode(PolygonMode.Fill);
            if (Keyboard[Key.F2]) SetPolygonMode(PolygonMode.Line);
            if (Keyboard[Key.F3]) this.controller.CrossfadeTo("Battloid-Transport");
            if (Keyboard[Key.F4]) this.controller.CrossfadeTo("Transport-Battloid");
            if (Keyboard[Key.F5]) this.controller.CrossfadeTo("Run");

            if (Keyboard[Key.Home]) chaseDistance -= 1;
            if (Keyboard[Key.End]) chaseDistance += 1;
        }

        //private void Game_KeyUp(KeyboardDevice keyboard, Key key)
        //{
        //    if (frameMgr.ConsumingKeyboard)
        //    {
        //        frameMgr.OnKeyUp(keyboard, key);
        //    }
        //}

        private void Game_KeyUp(object sender, KeyboardKeyEventArgs e) {
            if (frameMgr.ConsumingKeyboard) {
                frameMgr.OnKeyUp(sender, e);
            }
        }

        private Matrix4 projectionMatrix;
		public Matrix4 ProjectionMatrix
		{
			get
			{
				return projectionMatrix;
			}
		}
		
		private void SetupLighting()
		{
			GL.Enable(EnableCap.Lighting);
			GL.Enable(EnableCap.Light0);
			
			GL.Light(LightName.Light0, LightParameter.Ambient, new float[] {0.0f, 0.0f, 0.0f, 1.0f});
			GL.Light(LightName.Light0, LightParameter.Diffuse, new float[] {1.0f, 1.0f, 1.0f, 1.0f});
			GL.Light(LightName.Light0, LightParameter.Specular, new float[] {0.5f, 0.5f, 0.5f, 1.0f});
			GL.Light(LightName.Light0, LightParameter.Position, new float[] {100.0f, 10.0f, 1000.0f, 1.0f});
		}

        private PolygonMode polygonMode = PolygonMode.Fill;
        public void SetPolygonMode(PolygonMode polygonMode)
        {
            this.polygonMode = polygonMode;
        }
	
		private float chaseDistance = 10;
		private float cameraYaw = 0;
		private float cameraPitch = 0;

        private float actualFps;
        public float ActualFps
        {
            get
            {
                return actualFps;
            }
        }
		
		private DateTime start = DateTime.Now;
		private long frames = 0;
		private void UpdateActualFps()
		{
			frames++;

			if(DateTime.Now < start.AddSeconds(1)) return;

            actualFps = (float)(frames / (DateTime.Now - start).TotalSeconds);
			frames = 0;
			start = DateTime.Now;
		}

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
			UpdateActualFps();

            frameMgr.Update(e.Time);
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            GL.ClearColor(Color.CornflowerBlue);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
									
			GL.MatrixMode(MatrixMode.Projection);
			GL.LoadMatrix(OOGL.Matrix4Helper.ToOpenGL(ProjectionMatrix));

			Matrix4 viewMatrix = Matrix4.LookAt(new Vector3(0, 0, chaseDistance), Vector3.Zero, Vector3.UnitY);

            GL.PolygonMode(MaterialFace.FrontAndBack, this.polygonMode);
            model.Draw(controller, 0.025f, Matrix4.Rotate(Vector3.UnitY, Functions.PIF) * viewMatrix);
            ErrorChecking.TraceErrors();
			
            GL.PolygonMode(MaterialFace.FrontAndBack, PolygonMode.Fill);
            frameMgr.Draw(e.Time);

			SwapBuffers();
        }

        public override void Exit()
        {
            this.frameMgr.SaveWorkspace();

            base.Exit();
        }
		
		protected override void Dispose (bool manual)
		{
			base.Dispose (manual);			
		}

        [STAThread]
        static void Main()
        {
			TextWriterTraceListener listener = new TextWriterTraceListener(Console.Out);
			Trace.Listeners.Add(listener);
			
            using (Game game = new Game())
            {
                //game.RunSimple(60);
				game.Run(60, 60);
            }
        }
    }
}
