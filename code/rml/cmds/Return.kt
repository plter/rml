package rml.cmds

import rml.Scope

class Return(refName: String?, parent: Scope?, lineNum: Int, fileId: String) : Command(parent, lineNum, fileId) {

    private val _refName: String? = refName

    override fun execute(): Var? {
        if (_refName != null) {
            return getVar(_refName)
        }
        return null
    }
}