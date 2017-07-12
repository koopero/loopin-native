module.exports = executable

function executable( build ) {
  return Promise.resolve()
  .then( ()=> !build.quick && build.checkFile('${project.executable}') )
}
