package rml

abstract class RMLReader(source: String?) {

    private val _source = source

    fun read() {
        if (_source != null) {
            var index = 0
            val sourceLength = _source.length
            while (index < sourceLength) {
                var c = _source[index]
                if (c == '<') {
                    index += 1

                    c = _source[index]
                    when (c) {
                        '/' -> {
                            val endTagSB = StringBuilder()
                            index += 1
                            while (index < sourceLength) {
                                c = _source[index]

                                if (c != '>') {
                                    endTagSB.append(c)
                                } else {
                                    break
                                }
                                index++
                            }
                            elementEnd(endTagSB.toString())
                        }
                        '!' -> {
                            if (_source[index + 1] == '-' && _source[index + 2] == '-') {
                                index += 3
                                val contentSB = StringBuilder()
                                while (index < sourceLength) {
                                    c = _source[index]
                                    if (c == '-' && _source[index + 1] == '-' && _source[index + 2] == '>') {
                                        break
                                    } else {
                                        contentSB.append(c)
                                    }
                                    index++
                                }
                                commentContent(contentSB.toString())
                            }
                        }
                        else -> {
                            var sb = StringBuilder()
                            val attributes = HashMap<String, String>()
                            var tag: String? = null
                            loop@ while (index < sourceLength) {
                                c = _source[index]

                                when (c) {
                                    ' ' -> {
                                        if (tag == null) {
                                            tag = sb.toString()
                                        }
                                        sb = StringBuilder()
                                    }
                                    '=' -> {
                                        val name = sb.toString()
                                        val valueSB = StringBuilder()
                                        index += 1
                                        var foundStart = false
                                        while (index < sourceLength) {
                                            c = _source[index]
                                            if (c != '"') {
                                                if (foundStart) {
                                                    valueSB.append(c)
                                                }
                                            } else {
                                                if (!foundStart) {
                                                    foundStart = true
                                                } else {
                                                    val value = valueSB.toString()
                                                    attributes[name] = value
                                                    break
                                                }
                                            }

                                            index++
                                        }
                                    }
                                    '/' -> {
                                        if (tag == null) {
                                            tag = sb.toString()
                                        }
                                        if (_source[index + 1] == '>') {
                                            elementStart(tag, attributes)
                                            elementEnd(tag)
                                            break@loop
                                        } else {
                                            error("Syntax error")
                                        }
                                    }
                                    '>' -> {
                                        if (tag == null) {
                                            tag = sb.toString()
                                        }
                                        elementStart(tag, attributes)
                                        break@loop
                                    }
                                    else -> {
                                        sb.append(c)
                                    }
                                }

                                index++
                            }
                        }
                    }

                }

                index++
            }
        }
    }

    protected abstract fun elementStart(tagName: String, attributes: Map<String, String>)
    protected abstract fun elementEnd(tagName: String)
    protected abstract fun commentStart()
    protected abstract fun commentContent(content: String)
    protected abstract fun commentEnd()


}