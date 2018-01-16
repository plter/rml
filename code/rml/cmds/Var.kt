package rml.cmds

import rml.Scope

class Var(name: String?, value: Any?, refName: String?, parent: Scope?, lineNum: Int, fileId: String) : Command(parent, lineNum, fileId) {

    private var _name: String? = name
    private var _value: Any? = value
    private var _refName: String? = refName

    val name: String?
        get() = _name

    var value: Any?
        get() = _value
        set(v) {
            _value = v
        }

    /**
     * 执行后生成新的变量用于记录当前的运行状态
     */
    override fun execute(): Var? {
        var value: Any? = _value
        if (value == null && _refName != null) {
            value = getVar(_refName!!)?.value
        }
        return Var(_name, value, _refName, parent, lineNum, fileId)
    }

    override fun toString(): String {
        return "$value"
    }
}