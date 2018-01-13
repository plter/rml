package rml

class Var(name: String?, value: String?, refName: String?, parent: Scope?) : Scope(parent) {

    private var _name: String? = name
    private var _value: String? = value
    private var _refName: String? = refName

    init {
        if (_value == null && _refName != null) {
            _value = getVar(_refName!!)?.value
        }
    }

    val name: String?
        get() = _name

    val value: String?
        get() = _value
}