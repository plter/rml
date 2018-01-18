package rml.cmds

import rml.Context
import rml.funcs.CreateArray
import rml.funcs.CreateMap
import rml.funcs.Func
import rml.funcs.FuncState

open class Var(name: String?, value: Any?, refName: String?, parent: Context?, lineNum: Int, fileId: String) : Command(parent, lineNum, fileId) {

    private var _name: String? = name
    private var _value: Any? = value
    private var _refName: String? = refName
    val refName: String? get() = _refName

    var name: String?
        get() = _name
        set(value) {
            _name = value
        }

    var value: Any?
        get() = _value
        set(v) {
            _value = v
        }


    fun asString(): String? {
        return value as? String
    }

    fun asInt(): Int? {
        return asString()?.toInt()
    }

    fun asFunc(): Func? {
        return value as? Func
    }

    fun asRMLArray(): CreateArray.RMLArray? {
        return value as? CreateArray.RMLArray
    }

    fun asRMLMap(): CreateMap.RMLMap? {
        return value as? CreateMap.RMLMap
    }

    /**
     * 执行后生成新的变量用于记录当前的运行状态
     */
    override fun execute(): Var? {
        if (_value == null && _refName != null) {
            _value = (parent as? FuncState)?.getVar(_refName!!)?.value
            if (_value == null) {
                _value = (parent as? FuncState)?.getFunc(_refName!!)
            }
        }
        return this
    }

    override fun toString(): String {
        return "Var($value)"
    }

    override fun clone(): Command {
        return Var(name, value, _refName, parent, lineNum, fileId)
    }
}