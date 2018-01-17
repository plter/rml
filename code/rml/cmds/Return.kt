package rml.cmds

import rml.Context
import rml.funcs.FuncState

class Return(refName: String?, parent: Context?, lineNum: Int, fileId: String) : Command(parent, lineNum, fileId) {

    private val _refName: String? = refName

    override fun execute(): Var? {
        if (_refName != null) {
            return (parent as? FuncState)?.getVar(_refName)
        }
        return null
    }

    override fun clone(): Command {
        return Return(_refName, parent, lineNum, fileId)
    }
}