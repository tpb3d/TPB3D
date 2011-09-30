/*
 * Created by SharpDevelop.
 * User: Duckblaster
 * Date: 19/09/2011
 * Time: 4:23 p.m.
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using Mono.Addins;

namespace TPB3D
{
	class TPB3D
	{
        [STAThread]
		static void Main ()
		{
			AddinManager.Initialize ();
			AddinManager.Registry.Update ();
		
			//foreach (ICommand cmd in AddinManager.GetExtensionObjects<ICommand> ())
				//cmd.Run ();
		}
	}
}