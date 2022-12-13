// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "pch.h"
#include "DumpJsonCommand.h"
#include "Workflows/CompletionFlow.h"
#include "Workflows/ImportExportFlow.h"
#include "Workflows/WorkflowBase.h"
#include "Resources.h"

namespace AppInstaller::CLI
{
    using namespace std::string_view_literals;

    std::vector<Argument> DumpJsonCommand::GetArguments() const
    {
        return {
            Argument{ "output", 'o', Execution::Args::Type::OutputFile, Resource::String::OutputFileArgumentDescription, ArgumentType::Positional, true },
            Argument{ "source", 's', Execution::Args::Type::Source, Resource::String::ExportSourceArgumentDescription, ArgumentType::Standard },
            Argument{ "include-versions", Argument::NoAlias, Execution::Args::Type::IncludeVersions, Resource::String::ExportIncludeVersionsArgumentDescription, ArgumentType::Flag },
            Argument::ForType(Execution::Args::Type::AcceptSourceAgreements),
        };
    }

    Resource::LocString DumpJsonCommand::ShortDescription() const
    {
        return { Resource::String::DumpJsonCommandShortDescription };
    }

    Resource::LocString DumpJsonCommand::LongDescription() const
    {
        return { Resource::String::DumpJsonCommandLongDescription };
    }

    void DumpJsonCommand::Complete(Execution::Context& context, Execution::Args::Type valueType) const
    {
        if (valueType == Execution::Args::Type::OutputFile)
        {
            // Intentionally output nothing to allow pass through to filesystem.
            return;
        }

        if (valueType == Execution::Args::Type::Source)
        {
            context << Workflow::CompleteSourceName;
            return;
        }
    }

    std::string DumpJsonCommand::HelpLink() const
    {
        // TODO: Link?
        return "";
    }

    void DumpJsonCommand::ExecuteInternal(Execution::Context& context) const
    {
        context.SetFlags(Execution::ContextFlag::TreatSourceFailuresAsWarning);

        context <<
            Workflow::ReportExecutionStage(Workflow::ExecutionStage::Discovery) <<
            Workflow::OpenSource() <<
            Workflow::SearchSourceForMany <<
            Workflow::HandleSearchResultFailures <<
            Workflow::SelectVersionsToExport <<
            Workflow::ReportExecutionStage(Workflow::ExecutionStage::Execution) <<
            Workflow::WriteImportFile;
    }
}
