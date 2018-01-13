package rml

class Arg(value: String?, refName: String?, parent: Scope?) : Scope(parent) {

    private val _value = value

    private val _refName = refName

    fun getValue(): String? {
        if (_value != null) {
            return _value
        } else if (_refName != null) {
            return getVar(_refName)?.value
        } else {
            return null
        }
    }

}