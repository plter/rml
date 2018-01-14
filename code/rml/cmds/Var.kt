package rml.cmds

import rml.Scope

class Var(name: String?, value: String?, refName: String?, parent: Scope?) : Command(parent) {

    private var _name: String? = name
    private var _value: String? = value
    private var _refName: String? = refName

    val name: String?
        get() = _name

    var value: String?
        get() = _value
        set(v) {
            _value = v
        }

    /**
     * 执行后生成新的变量用于记录当前的运行状态
     */
    override fun execute(): Var? {
        var value: String? = _value
        if (value == null && _refName != null) {
            value = getVar(_refName!!)?.value
        }
        return Var(_name, value, _refName, parent)
    }
}