#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetGraphicName(short &Index, bool Filter)
{
	string Name = "";
	if(GenieFile->GraphicPointers[Index] == 0)
	{
		return "*Disabled*";
	}
	if(Filter)
	{
		short Selection[2];
		for(short loop=0; loop < 2; loop++)
		Selection[loop] = Graphics_Graphics_SearchFilters[loop]->GetSelection();

		if(Selection[0] > 0) // Internal name prevents
		for(short loop=0; loop < 2; loop++)
		{
			switch(Selection[loop])
			{
				case 1: // SLP
					Name += "SLP "+lexical_cast<string>(GenieFile->Graphics[Index].SLP);
					break;
				case 2: // Unknown 1
					Name += "U1 "+lexical_cast<string>((short)GenieFile->Graphics[Index].Unknown1);
					break;
				case 3: // Unknown 2
					Name += "U2 "+lexical_cast<string>((short)GenieFile->Graphics[Index].Unknown2);
					break;
				case 4: // Layer
					Name += "L "+lexical_cast<string>((short)GenieFile->Graphics[Index].Layer);
					break;
				case 5: // Unknown 3
					Name += "U3 "+lexical_cast<string>((short)GenieFile->Graphics[Index].Unknown3);
					break;
				case 6: // Unknown 4
					Name += "U4 "+lexical_cast<string>((short)GenieFile->Graphics[Index].Unknown4);
					break;
				case 7: // Replay
					Name += "R "+lexical_cast<string>((short)GenieFile->Graphics[Index].Replay);
					break;
				case 8: // Sound
					Name += "So "+lexical_cast<string>(GenieFile->Graphics[Index].SoundID);
					break;
				case 9: // Attack Sound Used
					Name += "U "+lexical_cast<string>((short)GenieFile->Graphics[Index].AttackSoundUsed);
					break;
				case 10: // Frame Count
					Name += "FC "+lexical_cast<string>(GenieFile->Graphics[Index].FrameCount);
					break;
				case 11: // Angle Count
					Name += "AC "+lexical_cast<string>(GenieFile->Graphics[Index].AngleCount);
					break;
				case 12: // Speed
					Name += "Sp "+lexical_cast<string>(GenieFile->Graphics[Index].Unknown13);
					break;
				case 13: // Frame Rate
					Name += "FR "+lexical_cast<string>(GenieFile->Graphics[Index].FrameRate);
					break;
				case 14: // Replay Delay
					Name += "RD "+lexical_cast<string>(GenieFile->Graphics[Index].ReplayDelay);
					break;
				case 15: // Sequence Type
					Name += "ST "+lexical_cast<string>((short)GenieFile->Graphics[Index].SequenceType);
					break;
				case 16: // Mirroring Mode
					Name += "T "+lexical_cast<string>(GenieFile->Graphics[Index].Type);
					break;
				case 17: // Pointer
					Name = lexical_cast<string>(GenieFile->GraphicPointers[Index]);
					break;
			}
			Name += ", ";
			if(Selection[loop+1] < 1) break; // Internal name breaks
		}
	}

	if(GenieFile->Graphics[Index].Name != "")
	{
		Name += GenieFile->Graphics[Index].Name;
	}
	else
	{
		Name += "New Graphic";
	}
	return Name;
}

void AGE_Frame::OnGraphicsSearch(wxCommandEvent &Event)
{
	ListGraphics(false);
}

void AGE_Frame::ListGraphics(bool Sized)
{
	wxString Name, CompareText;
	SearchText = Graphics_Graphics_Search->GetValue().Lower();
	ExcludeText = Graphics_Graphics_Search_R->GetValue().Lower();
	for(short loop=0; loop < 2; loop++)
	UseAnd[loop] = Graphics_Graphics_UseAnd[loop]->GetValue();

	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Graphics_Graphics_List->GetCount() > 0) Graphics_Graphics_List->Clear();

	short IDCount = 22, GraphicIDs[IDCount];
	if(Sized)
	{
		GraphicIDs[0] = Units_ComboBox_ConstructionGraphicID->GetSelection();
		GraphicIDs[1] = Units_ComboBox_SnowGraphicID->GetSelection();
		GraphicIDs[2] = Units_ComboBox_AttackGraphic->GetSelection();
		for(short loop=0; loop < 2; loop++)
		{
			GraphicIDs[loop+3] = Units_ComboBox_StandingGraphic[loop]->GetSelection();
			GraphicIDs[loop+5] = Units_ComboBox_GarrisonGraphic[loop]->GetSelection();
			GraphicIDs[loop+7] = Units_ComboBox_WalkingGraphic[loop]->GetSelection();
			GraphicIDs[loop+9] = Units_ComboBox_DyingGraphic[loop]->GetSelection();
			GraphicIDs[loop+19] = TerRestrict_ComboBox_Graphics[loop]->GetSelection();
		}
		GraphicIDs[11] = Units_ComboBox_AttackMissileDuplicationGraphic->GetSelection();
		for(short loop=0; loop < 6; loop++)
		GraphicIDs[loop+12] = UnitCommands_ComboBox_Graphics[loop]->GetSelection();
		GraphicIDs[18] = DamageGraphics_ComboBox_GraphicID->GetSelection();
		GraphicIDs[21] = GraphicDeltas_ComboBox_GraphicID->GetSelection();

		if(Units_ComboBox_ConstructionGraphicID->GetCount() > 0)
		{
			Units_ComboBox_ConstructionGraphicID->Clear();
		}
		if(Units_ComboBox_SnowGraphicID->GetCount() > 0)
		{
			Units_ComboBox_SnowGraphicID->Clear();
		}
		if(Units_ComboBox_AttackGraphic->GetCount() > 0)
		{
			Units_ComboBox_AttackGraphic->Clear();
		}
		for(short loop=0; loop < 2; loop++)
		{
			if(Units_ComboBox_StandingGraphic[loop]->GetCount() > 0)
			{
				Units_ComboBox_StandingGraphic[loop]->Clear();
			}
			if(Units_ComboBox_GarrisonGraphic[loop]->GetCount() > 0)
			{
				Units_ComboBox_GarrisonGraphic[loop]->Clear();
			}
			if(Units_ComboBox_WalkingGraphic[loop]->GetCount() > 0)
			{
				Units_ComboBox_WalkingGraphic[loop]->Clear();
			}
			if(Units_ComboBox_DyingGraphic[loop]->GetCount() > 0)
			{
				Units_ComboBox_DyingGraphic[loop]->Clear();
			}
			if(TerRestrict_ComboBox_Graphics[loop]->GetCount() > 0)
			{
				TerRestrict_ComboBox_Graphics[loop]->Clear();
			}
		}
		if(Units_ComboBox_AttackMissileDuplicationGraphic->GetCount() > 0)
		{
			Units_ComboBox_AttackMissileDuplicationGraphic->Clear();
		}
		for(short loop=0; loop < 6; loop++)
		if(UnitCommands_ComboBox_Graphics[loop]->GetCount() > 0)
		{
			UnitCommands_ComboBox_Graphics[loop]->Clear();
		}
		if(DamageGraphics_ComboBox_GraphicID->GetCount() > 0)
		{
			DamageGraphics_ComboBox_GraphicID->Clear();
		}
		if(GraphicDeltas_ComboBox_GraphicID->GetCount() > 0)
		{
			GraphicDeltas_ComboBox_GraphicID->Clear();
		}

		for(short loop=0; loop < IDCount; loop++)
		{
			if(GraphicIDs[loop] == wxNOT_FOUND)
			{
				GraphicIDs[loop] = 0;
			}
		}

		Units_ComboBox_ConstructionGraphicID->Append("-1 - None");
		Units_ComboBox_SnowGraphicID->Append("-1 - None");
		Units_ComboBox_AttackGraphic->Append("-1 - None");
		for(short loop=0; loop < 2; loop++)
		{
			Units_ComboBox_StandingGraphic[loop]->Append("-1 - None");
			Units_ComboBox_GarrisonGraphic[loop]->Append("-1 - None");
			Units_ComboBox_WalkingGraphic[loop]->Append("-1 - None");
			Units_ComboBox_DyingGraphic[loop]->Append("-1 - None");
			TerRestrict_ComboBox_Graphics[loop]->Append("-1 - None");
		}
		Units_ComboBox_AttackMissileDuplicationGraphic->Append("-1 - None");
		for(short loop=0; loop < 6; loop++)
		UnitCommands_ComboBox_Graphics[loop]->Append("-1 - None");
		DamageGraphics_ComboBox_GraphicID->Append("-1 - None");
		GraphicDeltas_ComboBox_GraphicID->Append("-1 - None");
	}

	for(short loop=0; loop < GenieFile->Graphics.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetGraphicName(loop, true);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			Graphics_Graphics_List->Append(Name, (void*)&GenieFile->Graphics[loop]);
		}
		if(Sized)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetGraphicName(loop);
			Units_ComboBox_ConstructionGraphicID->Append(Name);
			Units_ComboBox_SnowGraphicID->Append(Name);
			Units_ComboBox_AttackGraphic->Append(Name);
			for(short loop=0; loop < 2; loop++)
			{
				Units_ComboBox_StandingGraphic[loop]->Append(Name);
				Units_ComboBox_GarrisonGraphic[loop]->Append(Name);
				Units_ComboBox_WalkingGraphic[loop]->Append(Name);
				Units_ComboBox_DyingGraphic[loop]->Append(Name);
				TerRestrict_ComboBox_Graphics[loop]->Append(Name);
			}
			Units_ComboBox_AttackMissileDuplicationGraphic->Append(Name);
			for(short loop=0; loop < 6; loop++)
			UnitCommands_ComboBox_Graphics[loop]->Append(Name);
			DamageGraphics_ComboBox_GraphicID->Append(Name);
			GraphicDeltas_ComboBox_GraphicID->Append(Name);
		}
	}

	ListingFix(Selections, Graphics_Graphics_List);
	if(Sized)
	{
		Units_ComboBox_ConstructionGraphicID->SetSelection(GraphicIDs[0]);
		Units_ComboBox_SnowGraphicID->SetSelection(GraphicIDs[1]);
		Units_ComboBox_AttackGraphic->SetSelection(GraphicIDs[2]);
		for(short loop=0; loop < 2; loop++)
		{
			Units_ComboBox_StandingGraphic[loop]->SetSelection(GraphicIDs[loop+3]);
			Units_ComboBox_GarrisonGraphic[loop]->SetSelection(GraphicIDs[loop+5]);
			Units_ComboBox_WalkingGraphic[loop]->SetSelection(GraphicIDs[loop+7]);
			Units_ComboBox_DyingGraphic[loop]->SetSelection(GraphicIDs[loop+9]);
			TerRestrict_ComboBox_Graphics[loop]->SetSelection(GraphicIDs[loop+19]);
		}
		Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(GraphicIDs[11]);
		for(short loop=0; loop < 6; loop++)
		UnitCommands_ComboBox_Graphics[loop]->SetSelection(GraphicIDs[loop+12]);
		DamageGraphics_ComboBox_GraphicID->SetSelection(GraphicIDs[18]);
		GraphicDeltas_ComboBox_GraphicID->SetSelection(GraphicIDs[21]);
	}

	for(short loop=0; loop < 2; loop++)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnGraphicsSelect(E);
}

void AGE_Frame::OnGraphicsSelect(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		GraphicIDs.resize(Selections);
		genie::Graphic * GraphicPointer;
		for(short loop = Selections; loop--> 0;)
		{
			GraphicPointer = (genie::Graphic*)Graphics_Graphics_List->GetClientData(Items.Item(loop));
			GraphicIDs[loop] = (GraphicPointer - (&GenieFile->Graphics[0]));
		}
		Graphics_Name->ChangeValue(GraphicPointer->Name);
		Graphics_Name->Container = &GraphicPointer->Name;
		Graphics_Name2->ChangeValue(GraphicPointer->Name2);
		Graphics_Name2->Container = &GraphicPointer->Name2;
		Graphics_SLP->ChangeValue(lexical_cast<string>(GraphicPointer->SLP));
		Graphics_SLP->Container = &GraphicPointer->SLP;
		Graphics_Unknown1->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown1));
		Graphics_Unknown1->Container = &GraphicPointer->Unknown1;
		Graphics_Unknown2->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown2));
		Graphics_Unknown2->Container = &GraphicPointer->Unknown2;
		Graphics_FrameType->ChangeValue(lexical_cast<string>((short)GraphicPointer->Layer));
		Graphics_FrameType->Container = &GraphicPointer->Layer;
		Graphics_Unknown3->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown3));
		Graphics_Unknown3->Container = &GraphicPointer->Unknown3;
		Graphics_Unknown4->ChangeValue(lexical_cast<string>((short)GraphicPointer->Unknown4));
		Graphics_Unknown4->Container = &GraphicPointer->Unknown4;
		Graphics_Replay->ChangeValue(lexical_cast<string>((short)GraphicPointer->Replay));
		Graphics_Replay->Container = &GraphicPointer->Replay;
		for(short loop=0; loop < 4; loop++)
		{
			Graphics_Coordinates[loop]->ChangeValue(lexical_cast<string>(GraphicPointer->Coordinates[loop]));
			Graphics_Coordinates[loop]->Container = &GraphicPointer->Coordinates[loop];
		}
		Graphics_SoundID->ChangeValue(lexical_cast<string>(GraphicPointer->SoundID));
		Graphics_SoundID->Container = &GraphicPointer->SoundID;
		Graphics_ComboBox_SoundID->SetSelection(GraphicPointer->SoundID + 1);
		Graphics_AttackSoundUsed->ChangeValue(lexical_cast<string>((short)GraphicPointer->AttackSoundUsed));
		Graphics_AttackSoundUsed->Container = &GraphicPointer->AttackSoundUsed;
		Graphics_CheckBox_AttackSoundUsed->SetValue((bool)GraphicPointer->AttackSoundUsed);
		Graphics_FrameCount->ChangeValue(lexical_cast<string>(GraphicPointer->FrameCount));
		Graphics_FrameCount->Container = &GraphicPointer->FrameCount;
		Graphics_AngleCount->ChangeValue(lexical_cast<string>(GraphicPointer->AngleCount));
		Graphics_AngleCount->Container = &GraphicPointer->AngleCount;
		Graphics_Unknown13->ChangeValue(lexical_cast<string>(GraphicPointer->Unknown13));
		Graphics_Unknown13->Container = &GraphicPointer->Unknown13;
		Graphics_FrameRate->ChangeValue(lexical_cast<string>(GraphicPointer->FrameRate));
		Graphics_FrameRate->Container = &GraphicPointer->FrameRate;
		Graphics_ReplayDelay->ChangeValue(lexical_cast<string>(GraphicPointer->ReplayDelay));
		Graphics_ReplayDelay->Container = &GraphicPointer->ReplayDelay;
		Graphics_SequenceType->ChangeValue(lexical_cast<string>((short)GraphicPointer->SequenceType));
		Graphics_SequenceType->Container = &GraphicPointer->SequenceType;
		Graphics_ID->ChangeValue(lexical_cast<string>(GraphicPointer->ID));
		Graphics_ID->Container = &GraphicPointer->ID;
		if(GameVersion >= 2)
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(210, 230, 255));
			Graphics_TypeS->ChangeValue(lexical_cast<string>(GraphicPointer->Type));
		}
		else
		{
			Graphics_TypeS->SetBackgroundColour(wxColour(255, 235, 215));
			Graphics_TypeS->ChangeValue(lexical_cast<string>((short)GraphicPointer->Type));
		}
		Graphics_TypeS->Container = &GraphicPointer->Type;
		ListGraphicDeltas();
		ListGraphicAttackSounds();
	}
}

void AGE_Frame::OnGraphicsAdd(wxCommandEvent &Event)
{
	if(GenieFile != NULL)
	{
		wxBusyCursor WaitCursor;
		genie::Graphic Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->Graphics.push_back(Temp);
		GenieFile->GraphicPointers.push_back(1);
		if(EnableIDFix)
		GenieFile->Graphics[GenieFile->Graphics.size()-1].ID = (int16_t)(GenieFile->Graphics.size()-1); // ID Fix
		Added = true;
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsInsert(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Graphic Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->Graphics.insert(GenieFile->Graphics.begin() + GraphicIDs[0], Temp);
		GenieFile->GraphicPointers.insert(GenieFile->GraphicPointers.begin() + GraphicIDs[0], 1);
		if(EnableIDFix)
		for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); loop++) // ID Fix
		GenieFile->Graphics[loop].ID = (int16_t)loop;
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsDelete(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		{
			GenieFile->Graphics.erase(GenieFile->Graphics.begin() + GraphicIDs[loop]);
			GenieFile->GraphicPointers.erase(GenieFile->GraphicPointers.begin() + GraphicIDs[loop]);
		}
		if(EnableIDFix)
		for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); loop++) // ID Fix
		GenieFile->Graphics[loop].ID = (int16_t)loop;
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsCopy(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		copies->GraphicPointer.resize(Selections);
		copies->Graphic.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		{
			copies->GraphicPointer[loop] = GenieFile->GraphicPointers[GraphicIDs[loop]];
			copies->Graphic[loop] = GenieFile->Graphics[GraphicIDs[loop]];
		}
	}
}

void AGE_Frame::OnGraphicsPaste(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(copies->Graphic.size()+GraphicIDs[0] > GenieFile->Graphics.size())
		{
			GenieFile->GraphicPointers.resize(copies->GraphicPointer.size()+GraphicIDs[0]);
			GenieFile->Graphics.resize(copies->Graphic.size()+GraphicIDs[0]);
		}
		for(short loop=0; loop < copies->Graphic.size(); loop++)
		{
			GenieFile->GraphicPointers[GraphicIDs[0]+loop] = copies->GraphicPointer[loop];
			copies->Graphic[loop].setGameVersion(GenieVersion);
			GenieFile->Graphics[GraphicIDs[0]+loop] = copies->Graphic[loop];
			if(EnableIDFix)
			GenieFile->Graphics[GraphicIDs[0]+loop].ID = (int16_t)(GraphicIDs[0]+loop); // ID Fix
		}
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::Graphic Temp;
		GenieFile->GraphicPointers.insert(GenieFile->GraphicPointers.begin() + GraphicIDs[0], copies->GraphicPointer.size(), 0);
		GenieFile->Graphics.insert(GenieFile->Graphics.begin() + GraphicIDs[0], copies->Graphic.size(), Temp);
		for(short loop=0; loop < copies->Graphic.size(); loop++)
		{
			GenieFile->GraphicPointers[GraphicIDs[0]+loop] = copies->GraphicPointer[loop];
			copies->Graphic[loop].setGameVersion(GenieVersion);
			GenieFile->Graphics[GraphicIDs[0]+loop] = copies->Graphic[loop];
		}
		if(EnableIDFix)
		for(short loop = GraphicIDs[0];loop < GenieFile->Graphics.size(); loop++) // ID Fix
		GenieFile->Graphics[loop].ID = (int16_t)loop;
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsEnable(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop=0; loop < Selections; loop++)
		{
			GenieFile->GraphicPointers[GraphicIDs[loop]] = 1;
			GenieFile->Graphics[GraphicIDs[loop]].ID = (int16_t)GraphicIDs[loop]; // ID Fix
		}
		ListGraphics();
	}
}

void AGE_Frame::OnGraphicsDisable(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop=0; loop < Selections; loop++)
		GenieFile->GraphicPointers[GraphicIDs[loop]] = 0;
		ListGraphics();
	}
}

string AGE_Frame::GetGraphicDeltaName(short &Index)
{
	return "Graphic "+lexical_cast<string>(GenieFile->Graphics[GraphicIDs[0]].Deltas[Index].GraphicID)+" ";
}

void AGE_Frame::OnGraphicDeltasSearch(wxCommandEvent &Event)
{
	ListGraphicDeltas();
}

void AGE_Frame::ListGraphicDeltas()
{
	wxString Name, CompareText;
	SearchText = Graphics_Deltas_Search->GetValue().Lower();
	ExcludeText = Graphics_Deltas_Search_R->GetValue().Lower();

	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Graphics_Deltas_List->GetCount() > 0) Graphics_Deltas_List->Clear();

	for(short loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].Deltas.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetGraphicDeltaName(loop);
		CompareText = Name.Lower();
		if(SearchMatches(CompareText))
		{
			Graphics_Deltas_List->Append(Name, (void*)&GenieFile->Graphics[GraphicIDs[0]].Deltas[loop]);
		}
	}
	ListingFix(Selections, Graphics_Deltas_List);

	wxCommandEvent E;
	OnGraphicDeltasSelect(E);
}

void AGE_Frame::OnGraphicDeltasSelect(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		DeltaIDs.resize(Selections);
		genie::GraphicDelta * DeltaPointer;
		for(short loop = Selections; loop--> 0;)
		{
			DeltaPointer = (genie::GraphicDelta*)Graphics_Deltas_List->GetClientData(Items.Item(loop));
			DeltaIDs[loop] = (DeltaPointer - (&GenieFile->Graphics[GraphicIDs[0]].Deltas[0]));
		}
		GraphicDeltas_GraphicID->ChangeValue(lexical_cast<string>(DeltaPointer->GraphicID));
		GraphicDeltas_GraphicID->Container = &DeltaPointer->GraphicID;
		GraphicDeltas_ComboBox_GraphicID->SetSelection(DeltaPointer->GraphicID + 1);
		GraphicDeltas_Unknown1->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown1));
		GraphicDeltas_Unknown1->Container = &DeltaPointer->Unknown1;
		GraphicDeltas_Unknown2->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown2));
		GraphicDeltas_Unknown2->Container = &DeltaPointer->Unknown2;
		GraphicDeltas_Unknown3->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown3));
		GraphicDeltas_Unknown3->Container = &DeltaPointer->Unknown3;
		GraphicDeltas_DirectionX->ChangeValue(lexical_cast<string>(DeltaPointer->DirectionX));
		GraphicDeltas_DirectionX->Container = &DeltaPointer->DirectionX;
		GraphicDeltas_DirectionY->ChangeValue(lexical_cast<string>(DeltaPointer->DirectionY));
		GraphicDeltas_DirectionY->Container = &DeltaPointer->DirectionY;
		GraphicDeltas_Unknown4->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown4));
		GraphicDeltas_Unknown4->Container = &DeltaPointer->Unknown4;
		GraphicDeltas_Unknown5->ChangeValue(lexical_cast<string>(DeltaPointer->Unknown5));
		GraphicDeltas_Unknown5->Container = &DeltaPointer->Unknown5;
	}
	else
	{
		GraphicDeltas_GraphicID->ChangeValue("0");
		GraphicDeltas_ComboBox_GraphicID->SetSelection(0);
		GraphicDeltas_Unknown1->ChangeValue("0");
		GraphicDeltas_Unknown2->ChangeValue("0");
		GraphicDeltas_Unknown3->ChangeValue("0");
		GraphicDeltas_Unknown4->ChangeValue("0");
		GraphicDeltas_Unknown5->ChangeValue("0");
		GraphicDeltas_DirectionX->ChangeValue("0");
		GraphicDeltas_DirectionY->ChangeValue("0");
	}
}

void AGE_Frame::OnGraphicDeltasAdd(wxCommandEvent &Event)
{
	auto Selections = Graphics_Graphics_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::GraphicDelta Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->Graphics[GraphicIDs[0]].Deltas.push_back(Temp);
		Added = true;
		ListGraphicDeltas();
	}
}

void AGE_Frame::OnGraphicDeltasInsert(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::GraphicDelta Temp;
		Temp.setGameVersion(GenieVersion);
		GenieFile->Graphics[GraphicIDs[0]].Deltas.insert(GenieFile->Graphics[GraphicIDs[0]].Deltas.begin() + DeltaIDs[0], Temp);
		ListGraphicDeltas();
	}
}

void AGE_Frame::OnGraphicDeltasDelete(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		for(short loop = Selections; loop--> 0;)
		GenieFile->Graphics[GraphicIDs[0]].Deltas.erase(GenieFile->Graphics[GraphicIDs[0]].Deltas.begin() + DeltaIDs[loop]);
		ListGraphicDeltas();
	}
}

void AGE_Frame::OnGraphicDeltasCopy(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		copies->GraphicDelta.resize(Selections);
		for(short loop=0; loop < Selections; loop++)
		copies->GraphicDelta[loop] = GenieFile->Graphics[GraphicIDs[0]].Deltas[DeltaIDs[loop]];
	}
}

void AGE_Frame::OnGraphicDeltasPaste(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		if(copies->GraphicDelta.size()+DeltaIDs[0] > GenieFile->Graphics[GraphicIDs[0]].Deltas.size())
		GenieFile->Graphics[GraphicIDs[0]].Deltas.resize(copies->GraphicDelta.size()+DeltaIDs[0]);
		for(short loop=0; loop < copies->GraphicDelta.size(); loop++)
		{
			copies->GraphicDelta[loop].setGameVersion(GenieVersion);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[DeltaIDs[0]+loop] = copies->GraphicDelta[loop];
		}
		ListGraphicDeltas();
	}
}

void AGE_Frame::OnGraphicDeltasPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Graphics_Deltas_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::GraphicDelta Temp;
		GenieFile->Graphics[GraphicIDs[0]].Deltas.insert(GenieFile->Graphics[GraphicIDs[0]].Deltas.begin() + DeltaIDs[0], copies->GraphicDelta.size(), Temp);
		for(short loop=0; loop < copies->GraphicDelta.size(); loop++)
		{
			copies->GraphicDelta[loop].setGameVersion(GenieVersion);
			GenieFile->Graphics[GraphicIDs[0]].Deltas[DeltaIDs[0]+loop] = copies->GraphicDelta[loop];
		}
		ListGraphicDeltas();
	}
}

string AGE_Frame::GetGraphicAttackSoundName(short &Index)
{
	return "Attack sound "+lexical_cast<string>(Index);
}

void AGE_Frame::OnGraphicAttackSoundsSearch(wxCommandEvent &Event)
{
	ListGraphicAttackSounds();
}

void AGE_Frame::ListGraphicAttackSounds()
{
	string Name;

	auto Selections = Graphics_AttackSounds_List->GetSelections(Items);
	if(Graphics_AttackSounds_List->GetCount() > 0) Graphics_AttackSounds_List->Clear();

	for(short loop=0; loop < GenieFile->Graphics[GraphicIDs[0]].AttackSounds.size(); loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetGraphicAttackSoundName(loop);
		Graphics_AttackSounds_List->Append(Name, (void*)&GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop]);
	}

	ListingFix(Selections, Graphics_AttackSounds_List);

	wxCommandEvent E;
	OnGraphicAttackSoundsSelect(E);
}

void AGE_Frame::OnGraphicAttackSoundsSelect(wxCommandEvent &Event)
{
	auto Selections = Graphics_AttackSounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		AttackSoundIDs.resize(Selections);
		genie::GraphicAttackSound * AttackSoundPointer;
		for(short loop = Selections; loop--> 0;)
		{
			AttackSoundPointer = (genie::GraphicAttackSound*)Graphics_AttackSounds_List->GetClientData(Items.Item(loop));
			AttackSoundIDs[loop] = (AttackSoundPointer - (&GenieFile->Graphics[GraphicIDs[0]].AttackSounds[0]));
		}
		Graphics_AttackSoundID[0]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID));
		Graphics_AttackSoundID[0]->Container = &AttackSoundPointer->SoundID;
		Graphics_AttackSoundID[1]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID2));
		Graphics_AttackSoundID[1]->Container = &AttackSoundPointer->SoundID2;
		Graphics_AttackSoundID[2]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundID3));
		Graphics_AttackSoundID[2]->Container = &AttackSoundPointer->SoundID3;
		Graphics_ComboBox_AttackSoundID[0]->SetSelection(AttackSoundPointer->SoundID + 1);
		Graphics_ComboBox_AttackSoundID[1]->SetSelection(AttackSoundPointer->SoundID2 + 1);
		Graphics_ComboBox_AttackSoundID[2]->SetSelection(AttackSoundPointer->SoundID3 + 1);
		Graphics_AttackSoundDelay[0]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay));
		Graphics_AttackSoundDelay[0]->Container = &AttackSoundPointer->SoundDelay;
		Graphics_AttackSoundDelay[1]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay2));
		Graphics_AttackSoundDelay[1]->Container = &AttackSoundPointer->SoundDelay2;
		Graphics_AttackSoundDelay[2]->ChangeValue(lexical_cast<string>(AttackSoundPointer->SoundDelay3));
		Graphics_AttackSoundDelay[2]->Container = &AttackSoundPointer->SoundDelay3;
	}
	else
	{
		for(short loop=0; loop < 3; loop++)
		{
			Graphics_AttackSoundID[loop]->ChangeValue("0");
			Graphics_ComboBox_AttackSoundID[loop]->SetSelection(0);
			Graphics_AttackSoundDelay[loop]->ChangeValue("0");
		}
	}
}

void AGE_Frame::OnGraphicAttackSoundsCopy(wxCommandEvent &Event)
{
	auto Selections = Graphics_AttackSounds_List->GetSelections(Items);
	if(Selections != 0)
	{
		wxBusyCursor WaitCursor;
		genie::GraphicAttackSound Copy;
		Copy = GenieFile->Graphics[GraphicIDs[0]].AttackSounds[AttackSoundIDs[0]];
		for(short loop2=0; loop2 < GenieFile->Graphics[GraphicIDs[0]].AttackSounds.size(); loop2++)
		GenieFile->Graphics[GraphicIDs[0]].AttackSounds[loop2] = Copy;
	}
}

void AGE_Frame::CreateGraphicsControls()
{

	Tab_Graphics = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	Graphics_Main = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Graphics = new wxStaticBoxSizer(wxVERTICAL, Tab_Graphics, "Graphics  (Search by enter)");

	Graphics_Graphics_Search = new wxTextCtrl(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[0] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Graphics_Graphics_Search_R = new wxTextCtrl(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Graphics_Graphics_UseAnd[1] = new wxCheckBox(Tab_Graphics, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop=0; loop < 2; loop++)
	{
		Graphics_Graphics_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Graphics_Graphics_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Graphics, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Graphics_Graphics_List = new wxListBox(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Graphics_Graphics_Buttons = new wxGridSizer(3, 0, 0);
	Graphics_Add = new wxButton(Tab_Graphics, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Graphics_Insert = new wxButton(Tab_Graphics, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Graphics_Delete = new wxButton(Tab_Graphics, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Graphics_Copy = new wxButton(Tab_Graphics, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Graphics_Paste = new wxButton(Tab_Graphics, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Graphics_PasteInsert = new wxButton(Tab_Graphics, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Graphics_Extract = new wxButton(Tab_Graphics, wxID_ANY, "Extract", wxDefaultPosition, wxSize(5, 20));
	Graphics_Extract->Enable(false);
	Graphics_Import = new wxButton(Tab_Graphics, wxID_ANY, "Import", wxDefaultPosition, wxSize(5, 20));
	Graphics_Import->Enable(false);
	Graphics_Enable = new wxButton(Tab_Graphics, wxID_ANY, "Enable", wxDefaultPosition, wxSize(5, 20));
	Graphics_Disable = new wxButton(Tab_Graphics, wxID_ANY, "Disable", wxDefaultPosition, wxSize(5, 20));

	Graphics_DataArea = new wxBoxSizer(wxVERTICAL);
	Graphics_Scroller = new wxScrolledWindow(Tab_Graphics, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Graphics_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Graphics_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_NameArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name = new TextCtrl_String(Graphics_Scroller);
	Graphics_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Name2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Name2 = new TextCtrl_String(Graphics_Scroller);
	Graphics_Holder_ID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ID = new wxStaticText(Graphics_Scroller, wxID_ANY, " ID", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ID = new TextCtrl_Short(Graphics_Scroller);
	Graphics_Holder_Type = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Type = new wxStaticText(Graphics_Scroller, wxID_ANY, " Mirroring Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_TypeS = new TextCtrl_Short(Graphics_Scroller);
	Graphics_Holder_SequenceType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SequenceType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sequence Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SequenceType = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Holder_SLP = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SLP = new wxStaticText(Graphics_Scroller, wxID_ANY, " SLP", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SLP = new TextCtrl_Long(Graphics_Scroller);
	Graphics_Holder_FrameType = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameType = new wxStaticText(Graphics_Scroller, wxID_ANY, " Layer *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameType = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_FrameType->SetToolTip("0 - Cliffs\n5 - Shadows, Farms\n6 - Rubble\n10 - Construction sequences, some shadows, corpses, stumps, flowers, paths, ruins, crack\n11 - Fish\n19 - Rugs, crater\n20 - Buildings, damage flames, mill animation, units\n21 - Blacksmith piece (no slp), blacksmith smoke\n22 - Hawk\n30 - Explosions, projectiles ");
	Graphics_Holder_FrameCount = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameCount = new TextCtrl_UShort(Graphics_Scroller);
	Graphics_Holder_FrameRate = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_FrameRate = new wxStaticText(Graphics_Scroller, wxID_ANY, " Frame Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_FrameRate = new TextCtrl_Float(Graphics_Scroller);
	Graphics_FrameRate->SetToolTip("How long each frame is displayed in seconds");
	Graphics_Holder_SoundID = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_SoundID = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_SoundID = new TextCtrl_Short(Graphics_Scroller);
	Graphics_ComboBox_SoundID = new ComboBox_Short(Graphics_Scroller, Graphics_SoundID);
	Graphics_Holder_Replay = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Replay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Replay = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Replay->SetToolTip("Will the graphic be looped?");
	Graphics_Holder_ReplayDelay = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_ReplayDelay = new wxStaticText(Graphics_Scroller, wxID_ANY, " Replay Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_ReplayDelay = new TextCtrl_Float(Graphics_Scroller);
	Graphics_ReplayDelay->SetToolTip("Waiting time in seconds before animation restarts again");
	Graphics_Holder_Unknown13 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown13 = new wxStaticText(Graphics_Scroller, wxID_ANY, " New Speed? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown13 = new TextCtrl_Float(Graphics_Scroller);
	Graphics_Unknown13->SetToolTip("Speed value to override the unit's original one?");
	Graphics_Holder_4 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_5 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Grid_1 = new wxGridSizer(4, 5, 5);
	Graphics_Grid_2 = new wxGridSizer(4, 5, 5);

	Graphics_Deltas = new wxStaticBoxSizer(wxVERTICAL, Graphics_Scroller, "Deltas");
	Graphics_Deltas_Search = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_Search_R = new wxTextCtrl(Graphics_Scroller, wxID_ANY);
	Graphics_Deltas_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 140), 0, NULL, wxLB_EXTENDED);
	Graphics_Deltas_Buttons = new wxGridSizer(3, 0, 0);
	Deltas_Add = new wxButton(Graphics_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Deltas_Insert = new wxButton(Graphics_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Deltas_Delete = new wxButton(Graphics_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Deltas_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Deltas_Paste = new wxButton(Graphics_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Deltas_PasteInsert = new wxButton(Graphics_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	GraphicDeltas_Holder_GraphicID = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_GraphicID = new wxStaticText(Graphics_Scroller, wxID_ANY, " Graphic", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_GraphicID = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_ComboBox_GraphicID = new ComboBox_Short(Graphics_Scroller, GraphicDeltas_GraphicID);
	GraphicDeltas_Holder_DirectionX = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_DirectionX = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction X", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionX = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_DirectionY = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_DirectionY = new wxStaticText(Graphics_Scroller, wxID_ANY, " Direction Y", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_DirectionY = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown1 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown1 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown2 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown3 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown3 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown4 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown4 = new TextCtrl_Short(Graphics_Scroller);
	GraphicDeltas_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	GraphicDeltas_Text_Unknown5 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	GraphicDeltas_Unknown5 = new TextCtrl_Short(Graphics_Scroller);

	Graphics_AttackSounds = new wxStaticBoxSizer(wxVERTICAL, Graphics_Scroller, "Attack Sounds");
	Graphics_AttackSounds_List = new wxListBox(Graphics_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 140), 0, NULL, wxLB_EXTENDED);
	AttackSounds_Copy = new wxButton(Graphics_Scroller, wxID_ANY, "Copy to all", wxDefaultPosition, wxSize(10, 20));
	Graphics_Holder_AngleCount = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_AngleCount = new wxStaticText(Graphics_Scroller, wxID_ANY, " Angle Count", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AngleCount = new TextCtrl_UShort(Graphics_Scroller);
	Graphics_Holder_AttackSoundUsed = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_AttackSoundUsed1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Text_AttackSoundUsed = new wxStaticText(Graphics_Scroller, wxID_ANY, " Attack Sound Used", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_AttackSoundUsed = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_CheckBox_AttackSoundUsed = new CheckBox_Byte(Graphics_Scroller, "Used", Graphics_AttackSoundUsed);
	Graphics_Holder_AttackSounds = new wxBoxSizer(wxVERTICAL);
	Graphics_Grid_AttackSounds = new wxGridSizer(2, 0, 0);
	Graphics_Text_AttackSounds = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Holder_AttackSoundDelays = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_AttackSoundDelays = new wxStaticText(Graphics_Scroller, wxID_ANY, " Sound Delay", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 3; loop++)
	{
		Graphics_AttackSoundID[loop] = new TextCtrl_Short(Graphics_Scroller);
		Graphics_ComboBox_AttackSoundID[loop] = new ComboBox_Short(Graphics_Scroller, Graphics_AttackSoundID[loop]);
		Graphics_AttackSoundDelay[loop] = new TextCtrl_Short(Graphics_Scroller);
	}
	Graphics_Holder_Coordinates = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_CoordinateGrid = new wxGridSizer(4, 0, 5);
	Graphics_Text_Coordinates = new wxStaticText(Graphics_Scroller, wxID_ANY, " Coordinates", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop=0; loop < 4; loop++)
	Graphics_Coordinates[loop] = new TextCtrl_Short(Graphics_Scroller);
	Graphics_Holder_Unknowns = new wxGridSizer(4, 0, 5);
	Graphics_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown1 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown1 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown2 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown2 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown3 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown3 = new TextCtrl_Byte(Graphics_Scroller);
	Graphics_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	Graphics_Text_Unknown4 = new wxStaticText(Graphics_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Graphics_Unknown4 = new TextCtrl_Byte(Graphics_Scroller);

	Graphics_Holder_Deltas = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_Deltas_Data = new wxBoxSizer(wxVERTICAL);
	Graphics_Holder_Deltas_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Grid_Deltas_Data2 = new wxGridSizer(3, 5, 5);
	Graphics_Holder_AttackSoundArea = new wxBoxSizer(wxHORIZONTAL);
	Graphics_Holder_AttackSounds_Data = new wxBoxSizer(wxVERTICAL);

	for(short loop=0; loop < 2; loop++)
	{
		Graphics_Graphics_SearchFilters[loop]->Append("Internal Name");	// 0
		Graphics_Graphics_SearchFilters[loop]->Append("SLP");
		Graphics_Graphics_SearchFilters[loop]->Append("Unknown 1");
		Graphics_Graphics_SearchFilters[loop]->Append("Unknown 2");
		Graphics_Graphics_SearchFilters[loop]->Append("Layer");
		Graphics_Graphics_SearchFilters[loop]->Append("Unknown 3");
		Graphics_Graphics_SearchFilters[loop]->Append("Unknown 4");
		Graphics_Graphics_SearchFilters[loop]->Append("Replay");
		Graphics_Graphics_SearchFilters[loop]->Append("Sound");
		Graphics_Graphics_SearchFilters[loop]->Append("Attack Sound Used");
		Graphics_Graphics_SearchFilters[loop]->Append("Frame Count");
		Graphics_Graphics_SearchFilters[loop]->Append("Angle Count");
		Graphics_Graphics_SearchFilters[loop]->Append("Speed");
		Graphics_Graphics_SearchFilters[loop]->Append("Frame Rate");
		Graphics_Graphics_SearchFilters[loop]->Append("Replay Delay");
		Graphics_Graphics_SearchFilters[loop]->Append("Sequence Type");
		Graphics_Graphics_SearchFilters[loop]->Append("Mirroring Mode");
		Graphics_Graphics_SearchFilters[loop]->Append("Pointer");
		Graphics_Graphics_SearchFilters[loop]->SetSelection(0);
	}

	Graphics_Graphics_Buttons->Add(Graphics_Add, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Insert, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Delete, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Copy, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Paste, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_PasteInsert, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Extract, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Import, 1, wxEXPAND);
	Graphics_Graphics_Buttons->AddStretchSpacer(1);
	Graphics_Graphics_Buttons->Add(Graphics_Enable, 1, wxEXPAND);
	Graphics_Graphics_Buttons->Add(Graphics_Disable, 1, wxEXPAND);

	Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_Search, 1, wxEXPAND);
	Graphics_Graphics_Searches[0]->Add(2, -1);
	Graphics_Graphics_Searches[0]->Add(Graphics_Graphics_UseAnd[0], 0, wxEXPAND);
	Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_Search_R, 1, wxEXPAND);
	Graphics_Graphics_Searches[1]->Add(2, -1);
	Graphics_Graphics_Searches[1]->Add(Graphics_Graphics_UseAnd[1], 0, wxEXPAND);
	for(short loop=0; loop < 2; loop++)
	Graphics_Graphics->Add(Graphics_Graphics_Searches[loop], 0, wxEXPAND);
	for(short loop=0; loop < 2; loop++)
	Graphics_Graphics->Add(Graphics_Graphics_SearchFilters[loop], 0, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_List, 1, wxEXPAND);
	Graphics_Graphics->Add(-1, 2);
	Graphics_Graphics->Add(Graphics_Graphics_Buttons, 0, wxEXPAND);

	Graphics_ListArea->Add(-1, 10);
	Graphics_ListArea->Add(Graphics_Graphics, 1, wxEXPAND);
	Graphics_ListArea->Add(-1, 10);

	Graphics_Holder_Name->Add(Graphics_Text_Name, 0, wxEXPAND);
	Graphics_Holder_Name->Add(Graphics_Name, 1, wxEXPAND);
	Graphics_Holder_Name2->Add(Graphics_Text_Name2, 0, wxEXPAND);
	Graphics_Holder_Name2->Add(Graphics_Name2, 1, wxEXPAND);
	Graphics_Holder_ID->Add(Graphics_Text_ID, 0, wxEXPAND);
	Graphics_Holder_ID->Add(Graphics_ID, 1, wxEXPAND);
	Graphics_Holder_Unknown1->Add(Graphics_Text_Unknown1, 0, wxEXPAND);
	Graphics_Holder_Unknown1->Add(Graphics_Unknown1, 1, wxEXPAND);
	Graphics_Holder_Unknown2->Add(Graphics_Text_Unknown2, 0, wxEXPAND);
	Graphics_Holder_Unknown2->Add(Graphics_Unknown2, 1, wxEXPAND);
	Graphics_Holder_Unknown3->Add(Graphics_Text_Unknown3, 0, wxEXPAND);
	Graphics_Holder_Unknown3->Add(Graphics_Unknown3, 1, wxEXPAND);
	Graphics_Holder_Unknown4->Add(Graphics_Text_Unknown4, 0, wxEXPAND);
	Graphics_Holder_Unknown4->Add(Graphics_Unknown4, 1, wxEXPAND);
	for(short loop=0; loop < 4; loop++)
	Graphics_Holder_CoordinateGrid->Add(Graphics_Coordinates[loop], 1, wxEXPAND);
	Graphics_Holder_Coordinates->Add(Graphics_Text_Coordinates, 0, wxEXPAND);
	Graphics_Holder_Coordinates->Add(Graphics_Holder_CoordinateGrid, 1, wxEXPAND);
	Graphics_Holder_Unknown13->Add(Graphics_Text_Unknown13, 0, wxEXPAND);
	Graphics_Holder_Unknown13->Add(Graphics_Unknown13, 0, wxEXPAND);
	Graphics_Holder_SLP->Add(Graphics_Text_SLP, 0, wxEXPAND);
	Graphics_Holder_SLP->Add(Graphics_SLP, 1, wxEXPAND);
	Graphics_Holder_FrameType->Add(Graphics_Text_FrameType, 0, wxEXPAND);
	Graphics_Holder_FrameType->Add(Graphics_FrameType, 1, wxEXPAND);
	Graphics_Holder_Replay->Add(Graphics_Text_Replay, 0, wxEXPAND);
	Graphics_Holder_Replay->Add(Graphics_Replay, 0, wxEXPAND);
	Graphics_Holder_SoundID->Add(Graphics_Text_SoundID, 0, wxEXPAND);
	Graphics_Holder_SoundID->Add(Graphics_SoundID, 1, wxEXPAND);
	Graphics_Holder_SoundID->Add(Graphics_ComboBox_SoundID, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_AttackSoundUsed, 2, wxEXPAND);
	Graphics_Holder_AttackSoundUsed1->Add(2, -1);
	Graphics_Holder_AttackSoundUsed1->Add(Graphics_CheckBox_AttackSoundUsed, 1, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Text_AttackSoundUsed, 0, wxEXPAND);
	Graphics_Holder_AttackSoundUsed->Add(Graphics_Holder_AttackSoundUsed1, 1, wxEXPAND);
	Graphics_Holder_FrameCount->Add(Graphics_Text_FrameCount, 0, wxEXPAND);
	Graphics_Holder_FrameCount->Add(Graphics_FrameCount, 1, wxEXPAND);
	Graphics_Holder_AngleCount->Add(Graphics_Text_AngleCount, 0, wxEXPAND);
	Graphics_Holder_AngleCount->Add(Graphics_AngleCount, 1, wxEXPAND);
	Graphics_Holder_FrameRate->Add(Graphics_Text_FrameRate, 0, wxEXPAND);
	Graphics_Holder_FrameRate->Add(Graphics_FrameRate, 1, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(Graphics_Text_ReplayDelay, 0, wxEXPAND);
	Graphics_Holder_ReplayDelay->Add(Graphics_ReplayDelay, 0, wxEXPAND);
	Graphics_Holder_SequenceType->Add(Graphics_Text_SequenceType, 0, wxEXPAND);
	Graphics_Holder_SequenceType->Add(Graphics_SequenceType, 1, wxEXPAND);
	Graphics_Holder_Type->Add(Graphics_Text_Type, 0, wxEXPAND);
	Graphics_Holder_Type->Add(Graphics_TypeS, 1, wxEXPAND);

	Graphics_Holder_NameArea->Add(Graphics_Holder_Name, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_Name2, 2, wxEXPAND);
	Graphics_Holder_NameArea->Add(5, -1);
	Graphics_Holder_NameArea->Add(Graphics_Holder_ID, 1, wxEXPAND);

	Graphics_Grid_1->Add(Graphics_Holder_Type, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_SequenceType, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_SLP, 1, wxEXPAND);
	Graphics_Grid_1->AddStretchSpacer(1);
	Graphics_Grid_1->Add(Graphics_Holder_FrameType, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_FrameCount, 1, wxEXPAND);
	Graphics_Grid_1->Add(Graphics_Holder_FrameRate, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_SoundID, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_Replay, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_ReplayDelay, 1, wxEXPAND);
	Graphics_Grid_2->Add(Graphics_Holder_Unknown13, 1, wxEXPAND);

	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown1, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown2, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown3, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Graphics_Holder_Unknowns->Add(Graphics_Holder_Unknown4, 0, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Graphics_Deltas_Buttons->Add(Deltas_Add, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Insert, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Delete, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Copy, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_Paste, 1, wxEXPAND);
	Graphics_Deltas_Buttons->Add(Deltas_PasteInsert, 1, wxEXPAND);

	Graphics_Deltas->Add(Graphics_Deltas_Search, 0, wxEXPAND);
	Graphics_Deltas->Add(Graphics_Deltas_Search_R, 0, wxEXPAND);
	Graphics_Deltas->Add(-1, 2);
	Graphics_Deltas->Add(Graphics_Deltas_List, 1, wxEXPAND);
	Graphics_Deltas->Add(-1, 2);
	Graphics_Deltas->Add(Graphics_Deltas_Buttons, 0, wxEXPAND);

	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_Text_GraphicID, 0, wxEXPAND);
	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_GraphicID, 1, wxEXPAND);
	GraphicDeltas_Holder_GraphicID->Add(GraphicDeltas_ComboBox_GraphicID, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown1->Add(GraphicDeltas_Text_Unknown1, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown1->Add(GraphicDeltas_Unknown1, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown2->Add(GraphicDeltas_Text_Unknown2, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown2->Add(GraphicDeltas_Unknown2, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown3->Add(GraphicDeltas_Text_Unknown3, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown3->Add(GraphicDeltas_Unknown3, 1, wxEXPAND);
	GraphicDeltas_Holder_DirectionX->Add(GraphicDeltas_Text_DirectionX, 0, wxEXPAND);
	GraphicDeltas_Holder_DirectionX->Add(GraphicDeltas_DirectionX, 0, wxEXPAND);
	GraphicDeltas_Holder_DirectionY->Add(GraphicDeltas_Text_DirectionY, 0, wxEXPAND);
	GraphicDeltas_Holder_DirectionY->Add(GraphicDeltas_DirectionY, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown4->Add(GraphicDeltas_Text_Unknown4, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown4->Add(GraphicDeltas_Unknown4, 1, wxEXPAND);
	GraphicDeltas_Holder_Unknown5->Add(GraphicDeltas_Text_Unknown5, 0, wxEXPAND);
	GraphicDeltas_Holder_Unknown5->Add(GraphicDeltas_Unknown5, 1, wxEXPAND);

	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_GraphicID, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data1->Add(5, -1);
	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_DirectionX, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data1->Add(5, -1);
	Graphics_Holder_Deltas_Data1->Add(GraphicDeltas_Holder_DirectionY, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown1, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown2, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown3, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown4, 1, wxEXPAND);
	Graphics_Grid_Deltas_Data2->Add(GraphicDeltas_Holder_Unknown5, 1, wxEXPAND);
	Graphics_Holder_Deltas_Data->Add(Graphics_Holder_Deltas_Data1, 0, wxEXPAND);
	Graphics_Holder_Deltas_Data->Add(-1, 5);
	Graphics_Holder_Deltas_Data->Add(Graphics_Grid_Deltas_Data2, 0, wxEXPAND);

	Graphics_Holder_Deltas->Add(Graphics_Deltas, 1, wxEXPAND);
	Graphics_Holder_Deltas->Add(5, -1);
	Graphics_Holder_Deltas->Add(Graphics_Holder_Deltas_Data, 3, wxEXPAND);

	Graphics_AttackSounds->Add(Graphics_AttackSounds_List, 1, wxEXPAND);
	Graphics_AttackSounds->Add(-1, 2);
	Graphics_AttackSounds->Add(AttackSounds_Copy, 0, wxEXPAND);

	Graphics_Holder_AttackSounds->Add(Graphics_Text_AttackSounds, 0, wxEXPAND);
	Graphics_Holder_AttackSounds->Add(Graphics_Grid_AttackSounds, 0, wxEXPAND);
	Graphics_Holder_AttackSoundDelays->Add(Graphics_Text_AttackSoundDelays, 0, wxEXPAND);
	for(short loop=0; loop < 3; loop++)
	{
		Graphics_Grid_AttackSounds->Add(Graphics_AttackSoundID[loop], 0, wxEXPAND);
		Graphics_Grid_AttackSounds->Add(Graphics_ComboBox_AttackSoundID[loop], 0, wxEXPAND);
		Graphics_Holder_AttackSoundDelays->Add(Graphics_AttackSoundDelay[loop], 0, wxEXPAND);
	}
	Graphics_Holder_5->Add(Graphics_Holder_AttackSounds, 2, wxEXPAND);
	Graphics_Holder_5->Add(5, -1);
	Graphics_Holder_5->Add(Graphics_Holder_AttackSoundDelays, 1, wxEXPAND);

	Graphics_Holder_4->Add(Graphics_Holder_AngleCount, 1, wxEXPAND);
	Graphics_Holder_4->Add(5, -1);
	Graphics_Holder_4->Add(Graphics_Holder_AttackSoundUsed, 1, wxEXPAND);
	Graphics_Holder_4->AddStretchSpacer(1);

	Graphics_Holder_AttackSounds_Data->Add(Graphics_Holder_4, 0, wxEXPAND);
	Graphics_Holder_AttackSounds_Data->Add(-1, 5);
	Graphics_Holder_AttackSounds_Data->Add(Graphics_Holder_5, 0, wxEXPAND);

	Graphics_Holder_AttackSoundArea->Add(Graphics_AttackSounds, 1, wxEXPAND);
	Graphics_Holder_AttackSoundArea->Add(5, -1);
	Graphics_Holder_AttackSoundArea->Add(Graphics_Holder_AttackSounds_Data, 3, wxEXPAND);

	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_NameArea, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Grid_1, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Grid_2, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Deltas, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_AttackSoundArea, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Coordinates, 0, wxEXPAND);
	Graphics_ScrollerWindowsSpace->Add(-1, 5);
	Graphics_ScrollerWindowsSpace->Add(Graphics_Holder_Unknowns, 0, wxEXPAND);

	Graphics_ScrollerWindows->Add(Graphics_ScrollerWindowsSpace, 1, wxEXPAND);
	Graphics_ScrollerWindows->Add(5, -1);

	Graphics_Scroller->SetSizer(Graphics_ScrollerWindows);
	Graphics_Scroller->SetScrollRate(0, 15);

	Graphics_DataArea->Add(-1, 10);
	Graphics_DataArea->Add(Graphics_Scroller, 1, wxEXPAND);
	Graphics_DataArea->Add(-1, 10);

	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_ListArea, 1, wxEXPAND);
	Graphics_Main->Add(10, -1);
	Graphics_Main->Add(Graphics_DataArea, 3, wxEXPAND);
	Graphics_Main->Add(10, -1);

	if(EnableIDFix)
	Graphics_ID->Enable(false);

	Tab_Graphics->SetSizer(Graphics_Main);

	Connect(Graphics_Graphics_Search->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	Connect(Graphics_Graphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
	for(short loop=0; loop < 2; loop++)
	{
		Connect(Graphics_Graphics_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsSearch));
		Connect(Graphics_Graphics_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
	}
	Connect(Graphics_Graphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicsSelect));
	Connect(Graphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsAdd));
	Connect(Graphics_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsInsert));
	Connect(Graphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDelete));
	Connect(Graphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsCopy));
	Connect(Graphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPaste));
	Connect(Graphics_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsPasteInsert));
	Connect(Graphics_Extract->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnExtractGraphic));
	Connect(Graphics_Import->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnImportGraphic));
	Connect(Graphics_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsEnable));
	Connect(Graphics_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicsDisable));
	Connect(Graphics_Deltas_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSearch));
	Connect(Graphics_Deltas_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasSelect));
	Connect(Deltas_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasAdd));
	Connect(Deltas_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasInsert));
	Connect(Deltas_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasDelete));
	Connect(Deltas_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasCopy));
	Connect(Deltas_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPaste));
	Connect(Deltas_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicDeltasPasteInsert));
	Connect(Graphics_AttackSounds_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsSelect));
	Connect(AttackSounds_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnGraphicAttackSoundsCopy));

	Graphics_Name->Connect(Graphics_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Graphics_Name2->Connect(Graphics_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	GraphicDeltas_GraphicID->Connect(GraphicDeltas_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_ComboBoxShort), NULL, this);
	GraphicDeltas_ComboBox_GraphicID->Connect(GraphicDeltas_ComboBox_GraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_ComboBoxShort), NULL, this);
	Graphics_AngleCount->Connect(Graphics_AngleCount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_UnShort), NULL, this);
	Graphics_AttackSoundUsed->Connect(Graphics_AttackSoundUsed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_CheckBoxByte), NULL, this);
	Graphics_CheckBox_AttackSoundUsed->Connect(Graphics_CheckBox_AttackSoundUsed->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_CheckBoxByte), NULL, this);

}