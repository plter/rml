package rml.cmds

import rml.Context

class Arg(value: String?, refName: String?, parent: Context?, lineNum: Int, fileId: String) : Var(null, value, refName, parent, lineNum, fileId) {

    private val _value = value

    private val _refName = refName

    override fun clone(): Arg {
        return Arg(_value, _refName, parent, lineNum, fileId)
    }

}