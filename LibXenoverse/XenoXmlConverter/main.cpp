#include "LibXenoverse.h"









/*
//test for change type flags.

void recursiveChangeEmpTagName(TiXmlElement* parent, TiXmlElement* rootNode)
{
	/*
		}else if ((extension == "xml") && (extension2.substr(0,3) == "emp")) {				//test for analyzeXml from lazybone converter TODO remove, 

			
			
			TiXmlDocument doc(filename);
			if (!doc.LoadFile())
				return false;

			TiXmlHandle hDoc(&doc);
			TiXmlHandle hRoot(0);

			TiXmlElement* rootNode = hDoc.FirstChildElement("EMP").Element();
			if (rootNode)
				rootNode = rootNode->FirstChildElement("ParticleEffects");

			if (!rootNode)
			{
				printf("%s don't have 'EMP' and 'ParticleEffects' tags. skip.'\n", filename);
				getchar();
				return false;
			}

			recursiveChangeEmpTagName(rootNode, rootNode);

			doc.SaveFile(basefilename2 + "."+ extension2 +".xml");
		}
	
	*//*

	std::vector<TiXmlElement*> list;

	for (TiXmlElement* node = parent->FirstChildElement("ParticleEffect"); node; node = node->NextSiblingElement("ParticleEffect"))
	{
		recursiveChangeEmpTagName(node, rootNode);

		string attr = "";
		node->QueryStringAttribute("Data_Flags", &attr);

		if(attr.length())
			node->SetValue("ParticleEffect_"+ attr.substr(0, 1) + "_" + attr.substr(3, 1));

		list.push_back(node);
	}


	

	size_t nbNodes = list.size();
	for (size_t i = 0; i < nbNodes; i++)					//we do afer because the LinkEndChild() break the node->NextSiblingElement()
	{
		rootNode->LinkEndChild(list.at(i)->Clone());
		parent->RemoveChild(list.at(i));
	}
}
*/




int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: 'XenoXmlConverter.exe [-noEndWait] FILE.EXT FILE2.EXT ...' or 'XenoXmlConverter.exe FILE.EXT.xml FILE2.EXT.xml ...'\nFor Now, we only support sds, emm , emd , esk, ean, mat.ema, nsk, aur, emo files");
		getchar();
		return 1;
	}

	LibXenoverse::initializeDebuggingLog();

	bool endWaitEnable = true;
	for (int i = 1; i < argc; i++)
	{
		string filename = ToString(argv[i]);

		if (filename == "-noEndWait")
		{
			endWaitEnable = false;
			continue;
		}

		string extension = LibXenoverse::extensionFromFilename(filename, true);
		string basefilename = filename.substr(0, filename.length() - (extension.size() + 1)) ;
		string extension2 = LibXenoverse::extensionFromFilename(basefilename, true);
		string basefilename2 = basefilename.substr(0, basefilename.length() - (extension2.size() + 1));
		string extension3 = LibXenoverse::extensionFromFilename(basefilename2, true);
		string basefilename3 = basefilename2.substr(0, basefilename2.length() - (extension3.size() + 1));

	

		/////////////////////////////////////////////////////////////
		if (extension == "sds")
		{
			LibXenoverse::SDS* sds = new LibXenoverse::SDS();
			if(sds->load(filename))
				sds->saveXML(filename +".xml");
			delete sds;

		}else if ((extension == "xml")&&(extension2 == "sds")) {
			LibXenoverse::SDS* sds = new LibXenoverse::SDS();
			if(sds->load(filename))
				sds->save(basefilename2 + ".sds");
			delete sds;



		/////////////////////////////////////////////////////////////
		}else if (extension == "emm") {		// .emm  .ptcl.emm  .trc.emm  .tbind.emm  .pbind.emm
			
			if((extension2 == "tbind") || (extension2 == "pbind"))
			{
				printf("Error: .tbind.emm and .pbind.emm are not really like .emm file (there a EMB and a unknow EMP ETR flags. So skip. Sorry.\n");
				getchar();
				continue;
			}

			LibXenoverse::EMM* emm = new LibXenoverse::EMM();
			if (emm->load(filename))
				emm->saveXML(filename + ".xml");
			delete emm;

		}else if ((extension == "xml") && (extension2 == "emm") ) {

			LibXenoverse::EMM* emm = new LibXenoverse::EMM();
			if(emm->load(filename))
				emm->save(basefilename2 + ".emm");
			delete emm;





		/////////////////////////////////////////////////////////////
		}else if (extension == "emd") {
			LibXenoverse::EMD* emd = new LibXenoverse::EMD();
			if(emd->load(filename))
				emd->saveXml(filename + ".xml");
			delete emd;

		}else if ((extension == "xml") && (extension2 == "emd")) {

			LibXenoverse::EMD* emd = new LibXenoverse::EMD();
			if(emd->loadXml(filename))
				emd->save(basefilename2 + ".emd");
			delete emd;



		/////////////////////////////////////////////////////////////
		}else if (extension == "esk") {
			LibXenoverse::ESK* esk = new LibXenoverse::ESK();
			if (esk->load(filename))
				esk->saveXml(filename + ".xml");
			delete esk;

		}else if ((extension == "xml") && (extension2 == "esk"))  {

			LibXenoverse::ESK* esk = new LibXenoverse::ESK();
			if(esk->loadXml(filename))
				esk->save(basefilename2 + ".esk");
			delete esk;



		/////////////////////////////////////////////////////////////
		}else if (extension.substr(extension.length()-3) == "ean") {		//.ean, .fce.ean, .cam.ena
			LibXenoverse::EAN* ean = new LibXenoverse::EAN();
			if (ean->load(filename))
				ean->saveXml(filename + ".xml");
			delete ean;

		}else if ((extension == "xml") && (extension2 == "ean")) {

			LibXenoverse::EAN* ean = new LibXenoverse::EAN();
			if(ean->loadXml(filename))
				ean->save(basefilename2 + ".ean");
			delete ean;


		/////////////////////////////////////////////////////////////
		}
		else if (extension == "emo") {										//.emo
			LibXenoverse::EMO* emo = new LibXenoverse::EMO();
			if (emo->load(filename))
				emo->DecompileToFile(filename + ".xml");
			delete emo;

		}
		else if ((extension == "xml") && (extension2 == "emo")) {

			LibXenoverse::EMO* emo = new LibXenoverse::EMO();
			if (emo->load(filename))
				emo->SaveToFile(basefilename2 + ".emo");
			delete emo;


		/////////////////////////////////////////////////////////////
		}else if ((extension == "ema") && (extension2 == "mat")) {		//mat.ema
			LibXenoverse::EMA_Material* ema = new LibXenoverse::EMA_Material();
			if (ema->load(filename))
				ema->saveXml(filename + ".xml");
			delete ema;

		}else if ((extension == "xml") && (extension2 == "ema") && (extension3 == "mat")) {

			LibXenoverse::EMA_Material* ema = new LibXenoverse::EMA_Material();
			if (ema->loadXml(filename))
				ema->save(basefilename2 + ".ema");
			delete ema;



		/////////////////////////////////////////////////////////////
		}else if (extension == "nsk") {
			LibXenoverse::NSK* nsk = new LibXenoverse::NSK();
			if (nsk->load(filename))
				nsk->saveXml(filename + ".xml");
			delete nsk;

		}else if ((extension == "xml") && (extension2 == "nsk")) {

			LibXenoverse::NSK* nsk = new LibXenoverse::NSK();
			if (nsk->loadXml(filename))
				nsk->save(basefilename2 + ".nsk");
			delete nsk;



		/////////////////////////////////////////////////////////////
		}else if (extension == "aur") {
			LibXenoverse::AUR* aur = new LibXenoverse::AUR();
			if (aur->load(filename))
				aur->saveXml(filename + ".xml");
			delete aur;

		}else if ((extension == "xml") && (extension2 == "aur")) {

			LibXenoverse::AUR* aur = new LibXenoverse::AUR();
			if (aur->loadXml(filename))
				aur->save(basefilename2 + ".aur");
			delete aur;




		///////////////////////////////////////////////////////////// 
		}else if (extension == "etr") {
			LibXenoverse::Etr* etr = new LibXenoverse::Etr();
			if (etr->load(filename))
				etr->saveXml(filename + ".xml");
			delete etr;

		}else if ((extension == "xml") && (extension2 == "etr")) {

			LibXenoverse::Etr* etr = new LibXenoverse::Etr();
			if (etr->load(filename))
				etr->SaveToFile(basefilename2 + ".etr");
			delete etr;





		/////////////////////////////////////////////////////////////  For Tests/debug
		}else if (extension == "map") {

			LibXenoverse::FmpFile* fmp = new LibXenoverse::FmpFile();
			if (fmp->load(filename))
			{
				//fmp->SaveToFile(filename + "_modified.map");			//test Todo remove

				fmp->saveXml(filename + ".xml");
				
				//fmp->save_Xml(filename);								//test Xml version debug.
			}
			delete fmp;

		}else if ((extension == "xml") && (extension2 == "map")) {

			LibXenoverse::FmpFile* fmp = new LibXenoverse::FmpFile();
			fmp->originefilename = filename;
			if (fmp->load(filename))
				fmp->SaveToFile(basefilename2 + ".map");
			delete fmp;



		}else if (extension == "spm") {

			LibXenoverse::Spm* spm = new LibXenoverse::Spm();
			spm->save_Xml(filename);								//test Xml version debug.
			delete spm;

		}else if ((extension == "xml") && (extension2 == "spm")) {

			LibXenoverse::Spm* spm = new LibXenoverse::Spm();
			spm->originefilename = basefilename2 +".spm";
			spm->load(filename);						//also Save from Xml

			delete spm;
		}

	}

	printf("finished.\n");
	if(endWaitEnable)
		getchar();


	return 0;
}