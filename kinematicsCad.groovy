import com.neuronrobotics.bowlerstudio.creature.MobileBaseLoader
import com.neuronrobotics.bowlerstudio.scripting.ScriptingEngine
import com.neuronrobotics.bowlerstudio.threed.*;
import com.neuronrobotics.sdk.addons.kinematics.DHParameterKinematics
import com.neuronrobotics.sdk.addons.kinematics.MobileBase
import com.neuronrobotics.sdk.common.DeviceManager

import org.apache.commons.io.*
	
	import com.google.gson.Gson;
	import com.google.gson.GsonBuilder;
	import com.google.gson.reflect.TypeToken;
	import java.lang.reflect.Type;
	
	String myURL = "https://gist.github.com/aa464b39c1208c357b8d4ae7fe210bbb.git"
	String filename = "data.json"
	//GSON parts
	Type TT_mapStringString = new TypeToken<HashMap<String,Object>>() {}.getType();
	Gson gson = new GsonBuilder().disableHtmlEscaping().create();
	
	HashMap<String,Object> database = new HashMap<String,Object>()
	 
	


MobileBase base;
//Check if the device already exists in the device Manager
if(args==null){
	base=(MobileBase)DeviceManager.getSpecificDevice( "HephaestusArmV2_copy",{
			//If the device does not exist, prompt for the connection
			
			MobileBase m = MobileBaseLoader.fromGit(
				"https://github.com/Akshay5312/HephaestusArmV2_copy.git",
				"HephaestusArmV2_copy.xml"
				)
			if(m==null)
				throw new RuntimeException("Arm failed to assemble itself")
			println "Connecting new device robot arm "+m
			return m
		})
}else
	base=args.get(0)
	
def Limbs = base.getAllDHChains()
def LimbIndex = 0;
for(DHParameterKinematics limb: Limbs) {
	int NoLinks = limb.numberOfLinks
	def name = limb.getScriptingName()
	def limbRoot2D = limb.getRobotToFiducialTransform().getMatrixTransform().getArray()
	def limbRoot = [16]
	for(int r = 0; r<4; r++) {
		for(int k = 0; k<4; k++) {
			limbRoot[r*4+k] = limbRoot2D[r][k]
		}
	}
	database.put("limbRoot"+LimbIndex, limbRoot)
	
	database.put("LimbNames"+LimbIndex, name)

	println "name = "+ name + " limbRoot = " + limbRoot 
	
	for(int i = 0; i <NoLinks; i++) {
		def Alpha = limb.getDH_Alpha(i)
		def D = limb.getDH_D(i)
		def R = limb.getDH_R(i)
		def Theta = limb.getDH_Theta(i)
		
		def Offset =limb.getLinkConfiguration(i).getStaticOffset()
		def scale =100.0*limb.getLinkConfiguration(i).getScale()
		def Pin = limb.getLinkConfiguration(i).getHardwareIndex()
		database.put(LimbIndex+"Offset"+i, Offset)
		database.put(LimbIndex+"scale"+i, scale)
		database.put(LimbIndex+"HardwareIndex"+i, Pin)
		println "DH Parameters; Alpha = "+Math.toDegrees(Alpha)+" D = "+D+" R = "+R+" Theta = "+Math.toDegrees(Theta)
		def linkLimits = [limb.getMaxEngineeringUnits(i), limb.getMinEngineeringUnits(i)]
		
		database.put(LimbIndex+"Limit"+i, linkLimits)
		
		def LinkDH = []
		LinkDH.add(Alpha)
		LinkDH.add(D)
		LinkDH.add(R)
		LinkDH.add(Theta)		
		database.put(LimbIndex+"_DH_"+i,LinkDH)
	}
	
	database.put(LimbIndex+"_size", NoLinks)
	LimbIndex++;
}
database.put("Limbs_size", Limbs.size())




String writeOut = gson.toJson(database, TT_mapStringString);
println "New database JSON content = \n\n"+writeOut

def  fileName = "E:\\config.json"
File file = new File(fileName)
if(!file.exists()){file.createNewFile()}

BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
writer.write(writeOut);

writer.close();
