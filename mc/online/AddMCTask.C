MCTask* AddMCTask(TString name = "name", float trigPtLow=4, float trigPtHigh=8) {

  AliAnalysisManager *manage = AliAnalysisManager::GetAnalysisManager();

  if (!manage) return 0x0;

  if(!manage->GetInputEventHandler()) return 0x0;

  TString file_name = "MCTaskOutput.root";

  MCTask* task = new MCTask(name.Data(), trigPtLow, trigPtHigh);

  if(!task) return 0x0;

  manage->AddTask(task);

  manage->ConnectInput(task, 0, manage->GetCommonInputContainer());
  manage->ConnectOutput(task, 1, manage->CreateContainer("strangeMC", TList::Class(), AliAnalysisManager::kOutputContainer, file_name.Data()));

  return task;

}