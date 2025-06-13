#include <emscripten/bind.h>
#include <sstream>
#include <iomanip>
#include "function.hpp"
#include "translate.hpp"
#include "tee_streambuf.hpp"
#include"code.hpp"
// Function that returns HTML as a string
std::string generateHTML() {
    std::ostringstream html;
    
    // Check if we have valid instructions
    if(code.instruct.size() == 0) {
        html << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ATS - Debug Report</title>
    <style>
        body {
            font-family: 'Consolas', 'Monaco', 'Courier New', monospace;
            background: linear-gradient(135deg, #1a1a1a, #2d1b1b);
            color: #f0f0f0;
            text-align: center;
            padding: 50px;
        }
        .error-box {
            background: rgba(204, 0, 0, 0.1);
            border: 2px solid #cc0000;
            border-radius: 10px;
            padding: 30px;
            margin: 20px auto;
            max-width: 600px;
        }
    </style>
</head>
<body>
    <div class="error-box">
        <h1 style="color: #cc0000;">⚠️ No Instructions Found</h1>
        <p>You need to load and build code first before generating a report.</p>
        <p>Steps:</p>
        <ol style="text-align: left; max-width: 400px; margin: 20px auto;">
            <li>Enter your ATS assembly code</li>
            <li>Click "Build Code"</li>
            <li>Then click "Generate Report"</li>
        </ol>
    </div>
</body>
</html>)";
        return html.str();
    }
    
    html << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ATS - Debug Report</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Consolas', 'Monaco', 'Courier New', monospace;
            background: linear-gradient(135deg, #1a1a1a, #2d1b1b);
            color: #f0f0f0;
            line-height: 1.6;
            min-height: 100vh;
        }
        
        .container {
            max-width: 1400px;
            margin: 0 auto;
            padding: 20px;
        }
        
        .header {
            text-align: center;
            margin-bottom: 30px;
            padding: 20px;
            background: linear-gradient(45deg, #cc0000, #800000);
            border-radius: 10px;
            box-shadow: 0 4px 15px rgba(204, 0, 0, 0.3);
        }
        
        .header h1 {
            color: white;
            font-size: 2.5em;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);
            margin-bottom: 10px;
        }
        
        .header p {
            color: #ffcccc;
            font-size: 1.1em;
        }
        
        .stats-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin-bottom: 30px;
        }
        
        .stat-card {
            background: rgba(204, 0, 0, 0.1);
            border: 2px solid #cc0000;
            border-radius: 8px;
            padding: 15px;
            text-align: center;
        }
        
        .stat-card h3 {
            color: #cc0000;
            margin-bottom: 5px;
        }
        
        .stat-card .value {
            color: white;
            font-size: 1.5em;
            font-weight: bold;
        }
        
        .table-container {
            background: rgba(0, 0, 0, 0.7);
            border-radius: 10px;
            overflow: hidden;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.5);
            margin-bottom: 20px;
        }
        
        .table-title {
            background: linear-gradient(45deg, #cc0000, #990000);
            color: white;
            padding: 15px;
            font-size: 1.3em;
            font-weight: bold;
            text-align: center;
            text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.5);
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
            font-size: 0.9em;
        }
        
        th {
            background: linear-gradient(180deg, #800000, #600000);
            color: white;
            padding: 12px 8px;
            text-align: center;
            font-weight: bold;
            border-bottom: 2px solid #cc0000;
        }
        
        td {
            padding: 10px 8px;
            text-align: center;
            border-bottom: 1px solid #333;
            background: rgba(255, 255, 255, 0.02);
        }
        
        tr:nth-child(even) td {
            background: rgba(204, 0, 0, 0.05);
        }
        
        tr:hover td {
            background: rgba(204, 0, 0, 0.15);
            color: white;
        }
        
        .line-num { color: #ff6666; font-weight: bold; }
        .instruction { color: #ffcccc; font-family: 'Consolas', monospace; text-align: left; padding-left: 15px; }
        .machine-code { color: #66ff66; font-family: 'Consolas', monospace; font-weight: bold; }
        .address-mode { color: #ffff66; }
        .label { color: #ff9999; font-weight: bold; }
        .opcode { color: #99ccff; font-weight: bold; }
        .operand { color: #ccffcc; }
        
        .footer {
            text-align: center;
            margin-top: 30px;
            padding: 20px;
            background: rgba(0, 0, 0, 0.5);
            border-radius: 8px;
            color: #999;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🔧 ATS Debug Report</h1>
            <p> Script Assembly Analysis & Machine Code Generation</p>
        </div>
        
        <div class="stats-grid">
            <div class="stat-card">
                <h3>Total Instructions</h3>
                <div class="value">)" << code.instruct.size() << R"(</div>
            </div>
            <div class="stat-card">
                <h3>Code Size</h3>
                <div class="value">)" << code.instruct.size() * 2 << R"( bytes</div>
            </div>
            <div class="stat-card">
                <h3>Labels Found</h3>
                <div class="value">)";
    
    // Count labels safely
    int label_count = 0;
    try {
        for(unsigned int i = 0; i < code.instruct.size(); ++i) {
            if(code.instruct[i].label) label_count++;
        }
    } catch(...) {
        label_count = 0;
    }
    html << label_count;
    
    html << R"(</div>
            </div>
            <div class="stat-card">
                <h3>Memory Range</h3>
                <div class="value">$0000-$)" << std::hex << std::uppercase << (code.instruct.size() * 2) << std::dec << R"(</div>
            </div>
        </div>
        
        <div class="table-container">
            <div class="table-title">📋 Instruction Analysis</div>
            <table>
                <thead>
                    <tr>
                        <th>Index</th>
                        <th>Line #</th>
                        <th>Label</th>
                        <th>Instruction</th>
                        <th>Opcode</th>
                        <th>Address Mode</th>
                        <th>Operand</th>
                        <th>Machine Code</th>
                    </tr>
                </thead>
                <tbody>)";
    
    try {
        for(unsigned int i = 0; i < code.instruct.size(); ++i) {
            auto& inst = code.instruct[i];  
            std::string hex_code;
            try {
                hex_code = icode::instructionToHex(inst);
            } catch(...) {
                hex_code = "ERROR";
            }
            
            html << "                    <tr>\n";
            html << "                        <td class=\"line-num\">" << i << "</td>\n";
            html << "                        <td class=\"line-num\">" << inst.line_num << "</td>\n";
            
            // Label column
            if(inst.label) {
                html << "                        <td class=\"label\">" << inst.label_text << "</td>\n";
            } else {
                html << "                        <td>-</td>\n";
            }
            
            // Instruction text
            html << "                        <td class=\"instruction\">" << inst.text << "</td>\n";
            
            // Opcode (safely)
            try {
                html << "                        <td class=\"opcode\">" << icode::op_array[static_cast<unsigned int>(inst.opcode)] << "</td>\n";
            } catch(...) {
                html << "                        <td class=\"opcode\">ERROR</td>\n";
            }
            
            // Address mode (safely)
            try {
                html << "                        <td class=\"address-mode\">" << interp::add_mode[inst.mode] << "</td>\n";
            } catch(...) {
                html << "                        <td class=\"address-mode\">ERROR</td>\n";
            }
            
            // Operand info
            html << "                        <td class=\"operand\">";
            try {
                if(inst.op1.op_t == icode::op_type::OP_LABELTEXT) {
                    html << "Label: " << inst.op1.label_text;
                } else if(inst.op1.op_t == icode::op_type::OP_DECIMAL) {
                    html << "$" << std::hex << std::uppercase << (int)inst.op1.op << std::dec;
                } else if(inst.op1.op_t == icode::op_type::OP_MEMORY) {
                    html << "$" << std::hex << std::uppercase << inst.op1.op << std::dec;
                } else if(inst.op1.op_t == icode::op_type::OP_LABEL) {
                    html << "Line: " << inst.op1.op;
                } else {
                    html << "-";
                }
            } catch(...) {
                html << "ERROR";
            }
            html << "</td>\n";
            
            // Machine code
            html << "                        <td class=\"machine-code\">" << hex_code << "</td>\n";
            
            html << "                    </tr>\n";
        }
    } catch(...) {
        html << "                    <tr><td colspan=\"8\" style=\"color: #ff6666; text-align: center;\">Error processing instructions</td></tr>\n";
    }
    
    html << R"(                </tbody>
            </table>
        </div>
        
        <div class="footer">
            <p>Generated by ATS (Assembly Script) Debugger</p>
        </div>
    </div>
</body>
</html>)";
    
    return html.str();
}

// Add a global initialization function
bool initializeSystem() {
    static bool initialized = false;
    interp::mem_write = true; // Enable memory write tracking
    if (!initialized) {
        interp::setup_tee_for_interp_stream();
        code.reset();
        initialized = true;
        return true;
    }
    return true;
}

// Wrapper class for Emscripten
class ATSDebugger {
private:
    std::string last_error;
    bool code_loaded;
    bool code_built;
    bool execution_started;
    int current_instruction_index;
    
public:
    ATSDebugger() : code_loaded(false), code_built(false), execution_started(false), current_instruction_index(0) {
        initializeSystem(); // Ensure system is initialized
    }
    
    std::string getDebugHTML() {
        if (!code_built) {
            return R"(<!DOCTYPE html>
<html><body style="font-family: monospace; background: #1a1a1a; color: #ff6666; text-align: center; padding: 50px;">
<h1>⚠️ Code Not Built</h1>
<p>Please load and build your code first before generating a report.</p>
</body></html>)";
        }
        return generateHTML();
    }
    
    bool loadCode(const std::string& ats_code) {
        try {
            if (!interp::openLineString(ats_code)) {
                last_error = "Failed to load code from string: " + interp::comp_err.str();
                code_loaded = false;
                code_built = false;
                return false;
            }
            last_error.clear();
            code_loaded = true;
            code_built = false;
            execution_started = false;
            current_instruction_index = 0;
            return true;
        } catch (const std::exception& e) {
            last_error = std::string("Load error: ") + e.what();
            code_loaded = false;
            code_built = false;
            return false;
        }
    }
    
    bool buildCode() {
        if (!code_loaded) {
            last_error = "No code loaded - call loadCode first";
            return false;
        }
        try {
            code.reset();
            bool result = translate::build_code();
            if (!result) {
                last_error = interp::comp_err.str();
                code_built = false;
                return false;
            }
            last_error.clear();
            code_built = true;
            execution_started = false;
            current_instruction_index = 0;
            return true;
        } catch (const std::exception& e) {
            last_error = std::string("Build error: ") +  interp::comp_err.str();
            code_built = false;
            return false;
        }
    }
    
    bool startExecution() {
        if (!code_built) {
            last_error = "Code not built - cannot start execution";
            return false;
        }
        try {
            execution_started = true;
            current_instruction_index = 0;
            last_error.clear();
            return true;
        } catch (const std::exception& e) {
            last_error = std::string("Start execution error: ") + e.what();
            return false;
        }
    }
    
    bool stepInstruction() {
        if (!code_built) {
            last_error = "Code not built - cannot step";
            return false;
        }
        
        if (!execution_started) {
            execution_started = true;
            current_instruction_index = 0;
            code.proc.ip = 0;
        }
         
        try {
            int ip_before = code.proc.getIp();
            code.step();
            current_instruction_index = code.proc.getIp();
            if (current_instruction_index < 0 || current_instruction_index >= static_cast<int>(code.instruct.size())) {
                if (current_instruction_index >= static_cast<int>(code.instruct.size())) {
                    last_error = "End of program reached";
                    return false;
                }
            }
            
            last_error.clear();
            return true;
        } catch (const std::exception& e) {
            last_error = std::string("Step error: ") + e.what();
            return false;
        }
    }
    
    std::string getProcessorState() {
        std::ostringstream state;
        state << "{";
        state << "\"pc\":" << code.proc.getIp() << ",";
        state << "\"ac\":" << (int)code.proc.reg_a << ",";
        state << "\"x\":" << (int)code.proc.reg_x << ",";
        state << "\"y\":" << (int)code.proc.reg_y << ",";
        state << "\"sr\":" << (int)code.proc.valFlags() << ",";
        state << "\"sp\":" << (int)code.proc.sp << ",";
        
        state << "\"carry\":" << (code.proc.getFlag(icode::FLAG_CARRY) ? "true" : "false") << ",";
        state << "\"zero\":" << (code.proc.getFlag(icode::FLAG_ZERO) ? "true" : "false") << ",";
        state << "\"interrupt\":" << (code.proc.getFlag(icode::FLAG_INTERRUPT) ? "true" : "false") << ",";
        state << "\"decimal\":" << (code.proc.getFlag(icode::FLAG_DECIMAL) ? "true" : "false") << ",";
        state << "\"break\":" << (code.proc.getFlag(icode::FLAG_BREAK) ? "true" : "false") << ",";
        state << "\"overflow\":" << (code.proc.getFlag(icode::FLAG_OVERFLOW) ? "true" : "false") << ",";
        state << "\"negative\":" << (code.proc.getFlag(icode::FLAG_NEGATIVE) ? "true" : "false") << ",";
        
        state << "\"currentInstruction\":" << code.proc.getIp() << ",";
        state << "\"totalInstructions\":" << code.instruct.size();
        state << "}";
        return state.str();
    }

    std::string getCurrentInstructionInfo() {
        int nextIndex = execution_started ? code.proc.getIp() : 0;
        
        if (nextIndex < 0 || nextIndex >= static_cast<int>(code.instruct.size())) {
            return "{\"valid\":false}";
        }
        
        auto& inst = code.instruct[nextIndex];
        std::ostringstream info;
        info << "{";
        info << "\"valid\":true,";
        info << "\"index\":" << nextIndex << ",";
        info << "\"lineNum\":" << inst.line_num << ",";
        info << "\"text\":\"" << inst.text << "\",";
        info << "\"opcode\":\"" << icode::op_array[static_cast<unsigned int>(inst.opcode)] << "\",";
        info << "\"addressMode\":\"" << interp::add_mode[inst.mode] << "\",";
        
        if (inst.opcode == icode::opc::BNE || inst.opcode == icode::opc::BEQ || 
            inst.opcode == icode::opc::BCC || inst.opcode == icode::opc::BCS ||
            inst.opcode == icode::opc::BPL || inst.opcode == icode::opc::BMI ||
            inst.opcode == icode::opc::BVC || inst.opcode == icode::opc::BVS) {
            info << "\"isBranch\":true,";
            info << "\"branchTarget\":" << inst.op1.label_index << ",";
            
            bool zeroFlag = code.proc.getFlag(icode::FLAG_ZERO);
            info << "\"zeroFlag\":" << (zeroFlag ? "true" : "false") << ",";
            
            bool willBranch = false;
            switch (inst.opcode) {
                case icode::opc::BNE: willBranch = !zeroFlag; break;
                case icode::opc::BEQ: willBranch = zeroFlag; break;
            }
            info << "\"willBranch\":" << (willBranch ? "true" : "false") << ",";
        } else {
            info << "\"isBranch\":false,";
        }
        
        info << "\"actualIP\":" << code.proc.getIp();
        info << "}";
        return info.str();
    }
    
    void resetExecution() {
        execution_started = false;
        current_instruction_index = 0;
        if (code_built) {
            code.reset();
        }
    }
    
    bool isExecutionStarted() {
        return execution_started;
    }
    
    bool isExecutionComplete() {
        return execution_started && current_instruction_index >= static_cast<int>(code.instruct.size());
    }
    
    int getInstructionCount() {
        return static_cast<int>(code.instruct.size());
    }
    
    std::string getLastError() {
        return last_error;
    }
    
    bool isCodeLoaded() {
        return code_loaded;
    }
    
    bool isCodeBuilt() {
        return code_built;
    }
    
    std::string getMemoryState() {
        std::ostringstream memory;
        memory << "{";
        memory << "\"size\":65536,";
        memory << "\"data\":[";
        
        // Output memory as array of bytes
        for (int i = 0; i < 65536; i++) {
            if (i > 0) memory << ",";
            memory << (int)code.peek(i);
        }
        
        memory << "],";
        memory << "\"modified\":[";
        
        // Track which addresses were modified (you'd need to implement this tracking)
        // For now, return empty array
        memory << "]";
        memory << "}";
        return memory.str();
    }


    std::string getModifiedMemory() {
        std::ostringstream result;
        result << "[";
        for (size_t i = 0; i < interp::modifiedMemoryAddresses.size(); i++) {
            if (i > 0) result << ",";
            result << "{\"address\":" << interp::modifiedMemoryAddresses[i].first 
                << ",\"value\":" << (int)interp::modifiedMemoryAddresses[i].second << "}";
        }
        result << "]";
        return result.str();
    }

};

// Emscripten bindings
EMSCRIPTEN_BINDINGS(ats_module) {
    emscripten::class_<ATSDebugger>("ATSDebugger")
        .constructor<>()
        .function("loadCode", &ATSDebugger::loadCode)
        .function("buildCode", &ATSDebugger::buildCode)
        .function("getDebugHTML", &ATSDebugger::getDebugHTML)
        .function("getInstructionCount", &ATSDebugger::getInstructionCount)
        .function("getLastError", &ATSDebugger::getLastError)
        .function("startExecution", &ATSDebugger::startExecution)
        .function("stepInstruction", &ATSDebugger::stepInstruction)
        .function("resetExecution", &ATSDebugger::resetExecution)
        .function("getProcessorState", &ATSDebugger::getProcessorState)
        .function("getCurrentInstructionInfo", &ATSDebugger::getCurrentInstructionInfo)
        .function("getMemoryState", &ATSDebugger::getMemoryState)
        .function("getModifiedMemory", &ATSDebugger::getModifiedMemory);
    
    // Standalone function
    emscripten::function("generateHTML", &generateHTML);
}