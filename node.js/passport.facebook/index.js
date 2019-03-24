const express = require ('express')
const app = express ()
const path = require ('path')



app.use(express.static(path.join(__dirname, '/view')))

app.get ("/",)


app.listen(80, _ => console.log('\n\n\tApp Facebook Auth with passport.facebook module .............starting. \n\n listening on port 80'))